#pragma once

#include <vector>

#include "AbstractExpressionNode.cpp"
#include "operators/OperatorExpressionPair.cpp"

class BinaryOperatorExpressionNode : public AbstractExpressionNode
{
   public:
    BinaryOperatorExpressionNode(AbstractExpressionNode* firstExpression, std::vector<OperatorExpressionPair*> operatorExpressionPairs)
        : AbstractExpressionNode()
    {
        this->firstExpression = firstExpression;
        this->operatorExpressionPairs = operatorExpressionPairs;
    }
    ~BinaryOperatorExpressionNode()
    {
        delete firstExpression;

        for (OperatorExpressionPair* pair : operatorExpressionPairs)
        {
            delete pair;
        }
    }

    virtual bool RequiresAXRegister() override { return true; }

    virtual std::shared_ptr<Variable> TraverseExpression(CodeGenerator* codeGenerator, AssemblyCode* assemblyCode) override
    {
        std::shared_ptr<Variable> firstVariable = this->firstExpression->TraverseExpression(codeGenerator, assemblyCode);

        auto operatorExpressionIterator = this->operatorExpressionPairs.begin();

        // If there are no operators, return the first variable
        if (operatorExpressionIterator == this->operatorExpressionPairs.end())
        {
            return firstVariable;
        }

        std::shared_ptr<Variable> left = nullptr;

        if (firstVariable->IsInline())
        {
            left = firstVariable;
        }
        else
        {
            // Assign first to AX register
            left = std::shared_ptr<Variable>(codeGenerator->GetAXRegisterVariable(firstVariable->type, false, assemblyCode));
            codeGenerator->ApplyBinaryOperatorOnVariables(left, firstVariable, EOperators::ASSIGN_OPERATOR, assemblyCode);
        }

        while (operatorExpressionIterator != this->operatorExpressionPairs.end())
        {
            OperatorExpressionPair* operatorExpression = *operatorExpressionIterator;
            AbstractExpressionNode* rightExpression = operatorExpression->expression;
            bool requiresAXRegister = rightExpression->RequiresAXRegister() && left->location->IsRegister();
            std::shared_ptr<Variable> stackLocation = nullptr;

            if (requiresAXRegister)
            {
                // Push left to stack as AX will be used by rightExpression
                stackLocation = std::shared_ptr<Variable>(codeGenerator->GetNewLocalVariable(left->type, false, assemblyCode));
                codeGenerator->ApplyBinaryOperatorOnVariables(stackLocation, left, EOperators::ASSIGN_OPERATOR, assemblyCode);
            }

            std::shared_ptr<Variable> right = rightExpression->TraverseExpression(codeGenerator, assemblyCode);

            if (requiresAXRegister)
            {
                if (right->location->IsRegister())
                {
                    // Safes the result (AX register) in DX register
                    std::shared_ptr<IVariableLocation> DXregister =
                        std::shared_ptr<IVariableLocation>(AssemblyCodeGenerator.GetNewDXRegisterVarLocation(right->type->GetSize(), assemblyCode));
                    right->type->GenerateAssign(DXregister, right->location, assemblyCode);
                    right = std::shared_ptr<Variable>(new Variable(DXregister, right->type, right->isFinal));
                }

                // Pop left from stack
                codeGenerator->ApplyBinaryOperatorOnVariables(left, stackLocation, EOperators::ASSIGN_OPERATOR, assemblyCode);
            }

            left = codeGenerator->ApplyBinaryOperatorOnVariables(left, right, operatorExpression->op, assemblyCode);
            operatorExpressionIterator++;
        }

        left->isFinal = true;  // Make the result final
        return std::shared_ptr<Variable>(left);
    }

    virtual void TraverseConditionalJump(std::string label, bool inverseCondition, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode) override
    {
        // --- If last operator is not a comparison operator, use standard implementation ---
        OperatorExpressionPair* lastOperatorExpression = operatorExpressionPairs.back();

        if (!codeGenerator->IsConditionalOperator(lastOperatorExpression->op))  // Standard implementation
        {
            AbstractExpressionNode::TraverseConditionalJump(label, inverseCondition, codeGenerator, assemblyCode);
            return;
        }

        // --- Generate optimized conditional jump ---

        // Last expression is removed from the list, as it needn't be processed
        operatorExpressionPairs.pop_back();

        std::shared_ptr<Variable> left = this->TraverseExpression(codeGenerator, assemblyCode);
        std::shared_ptr<Variable> right = lastOperatorExpression->expression->TraverseExpression(codeGenerator, assemblyCode);

        // Generate conditional jump
        codeGenerator->GenerateConditionalJump(left, right, inverseCondition, lastOperatorExpression->op, label, assemblyCode);
    }

    virtual std::string ToString() override
    {
        std::string result = firstExpression->ToString();

        for (OperatorExpressionPair* pair : operatorExpressionPairs)
        {
            result += pair->ToString();
        }

        return result;
    }

    AbstractExpressionNode* firstExpression;
    std::vector<OperatorExpressionPair*> operatorExpressionPairs;
};
