#pragma once

#include "../../expression/AbstractExpressionNode.cpp"
#include "AbstractKeywordStatementNode.cpp"

class ReturnStatementNode : public AbstractKeywordStatementNode
{
   public:
    ReturnStatementNode(AbstractExpressionNode* expression) : AbstractKeywordStatementNode() { this->expression = expression; }
    ~ReturnStatementNode() { delete expression; }

    virtual void Traverse(CodeGenerator* codeGenerator, AssemblyCode* assemblyCode) override
    {
        // forget local variables
        AssemblyCodeGenerator.AddPostBody(assemblyCode);

        // store return as new local variable
        if (this->expression != nullptr)
        {
            std::shared_ptr<Variable> value = this->expression->TraverseExpression(codeGenerator, assemblyCode);

            // store return value to stack
            std::shared_ptr<IVariableLocation> returnLocation =
                std::shared_ptr<IVariableLocation>(AssemblyCodeGenerator.GetReturnLocation(value->type->GetSize(), assemblyCode));
            value->type->GenerateAssign(returnLocation, value->location, assemblyCode);

            // store return location to rax
            AssemblyCodeGenerator.MoveReturnLocationToRax(value->type->GetSize(), assemblyCode);
        }

        // return
        assemblyCode->AddLine(new AssemblyInstructionLine("ret"));
    }

    virtual std::string ToString() override
    {
        if (expression == nullptr)
        {
            return "return;";
        }

        return "return " + expression->ToString() + ";";
    }

    AbstractExpressionNode* expression;
};