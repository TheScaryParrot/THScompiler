#pragma once

#include "AbstractVarDeclarationNode.cpp"

class LocalVarDeclarationNode : public AbstractVarDeclarationNode
{
   public:
    LocalVarDeclarationNode(VarDeclarationAttributes attributes, TypeNode type, std::string name, AbstractExpressionNode* value)
        : AbstractVarDeclarationNode(attributes, type, name, value)
    {
    }

    virtual void Traverse(CodeGenerator* codeGenerator, AssemblyCode* assemblyCode) override
    {
        bool isFinal = this->attributes.isFinal;
        bool isInline = this->attributes.isInline;
        std::shared_ptr<Type> type = codeGenerator->GetType(this->type.name);

        std::shared_ptr<Variable> value = nullptr;

        if (this->value != nullptr)
        {
            value = this->value->TraverseExpression(codeGenerator, assemblyCode);
        }

        std::shared_ptr<Variable> newVariable = nullptr;

        if (isInline)
        {
            if (value == nullptr)
            {
                newVariable.reset(new Variable(nullptr, type, isFinal));
            }
            else
            {
                if (!value->IsInline())
                {
                    Logger.Log("Cannot assign a non-inline value to inline variable " + this->name, Logger::ERROR);
                    return;
                }

                if (value->type != type)
                {
                    Logger.Log("Assign types of inline variable " + this->name + " don't match", Logger::ERROR);
                    return;
                }

                newVariable.reset(new Variable(value->location, type, isFinal));
            }
        }
        else
        {
            newVariable.reset(codeGenerator->GetNewLocalVariable(type, isFinal, assemblyCode));

            if (value != nullptr)
            {
                codeGenerator->ApplyBinaryOperatorOnVariables(newVariable, value, EOperators::ASSIGN_OPERATOR, assemblyCode);
            }
        }

        codeGenerator->AddVariable(this->name, newVariable);
    }

    virtual std::string ToString() override { return "local " + AbstractVarDeclarationNode::ToString(); }
};