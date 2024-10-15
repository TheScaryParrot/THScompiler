#pragma once

#include "AbstractExpressionNode.cpp"
#include "operators/EUnaryOperators.cpp"

class UnaryOperatorExpressionNode : public AbstractExpressionNode
{
   public:
    UnaryOperatorExpressionNode(EPreUnaryOperators preUnaryOperator, AbstractExpressionNode* value, EPostUnaryOperators postUnaryOperator,
                                bool applyToReference)
        : AbstractExpressionNode()
    {
        this->preUnaryOperator = preUnaryOperator;
        this->value = value;
        this->postUnaryOperator = postUnaryOperator;
    }

    ~UnaryOperatorExpressionNode() { delete value; }

    virtual bool RequiresAXRegister() override { return false; }

    virtual std::shared_ptr<Variable> TraverseExpression(CodeGenerator* codeGenerator, AssemblyCode* assemblyCode) override
    {
        // TODO: Unary operators
        Logger.Log("Unary operators are not implemented yet", Logger::ERROR);
        return nullptr;

        std::shared_ptr<Variable> variable = this->value->TraverseExpression(codeGenerator, assemblyCode);

        if (!this->applyToReference)
        {
            std::shared_ptr<Variable> newVariable =
                std::shared_ptr<Variable>(codeGenerator->GetNewLocalVariable(variable->type, false, assemblyCode));
            codeGenerator->ApplyBinaryOperatorOnVariables(newVariable, variable, EOperators::ASSIGN_OPERATOR, assemblyCode);
            variable = newVariable;
        }

        switch (this->preUnaryOperator)
        {
            case EPreUnaryOperators::PRE_NOT:
                variable->type->GenerateNot(variable->location, assemblyCode);
                break;
            case EPreUnaryOperators::PRE_NEGATE:
                variable->type->GenerateNeg(variable->location, assemblyCode);
                break;
            case EPreUnaryOperators::PRE_INCREMENT:
                variable->type->GenerateInc(variable->location, assemblyCode);
                break;
            case EPreUnaryOperators::PRE_DECREMENT:
                variable->type->GenerateDec(variable->location, assemblyCode);
                break;
        }

        // TODO: Post unary operators

        return variable;
    }

    virtual std::string ToString() override
    {
        return EPreUnaryOperatorsToString(preUnaryOperator) + value->ToString() + EPostUnaryOperatorsToString(postUnaryOperator);
    }

    EPreUnaryOperators preUnaryOperator;
    AbstractExpressionNode* value;
    EPostUnaryOperators postUnaryOperator;
    ///@brief Whether the operator should be applied to the reference of the value. For ++ this is true, for ! this is false
    bool applyToReference;
};
