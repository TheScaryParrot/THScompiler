#pragma once

#include "../../../../codeGenerator/varLocation/LabelVarLocation.cpp"
#include "AbstractVarDeclarationNode.cpp"

class GlobalVarDeclarationNode : public AbstractVarDeclarationNode
{
   public:
    GlobalVarDeclarationNode(VarDeclarationAttributes attributes, TypeNode type, std::string name, AbstractExpressionNode* value)
        : AbstractVarDeclarationNode(attributes, type, name, value)
    {
    }

    virtual void Traverse(CodeGenerator* codeGenerator, AssemblyCode* assemblyCode) override
    {
        if (codeGenerator->DoesVariableExist(this->name))
        {
            Logger.Log("Variable " + this->name + " already exists. Cannot be declared again", Logger::ERROR);
            return;
        }

        std::shared_ptr<Type> type = codeGenerator->GetType(this->type.name);
        Variable* newVariable = nullptr;

        // bss and no inline allowed
        if (this->value == nullptr)
        {
            if (this->attributes.isInline)
            {
                Logger.Log("Cannot declare inline global variable " + this->name + " without value", Logger::ERROR);
                return;
            }

            std::shared_ptr<LabelVarLocation> location = std::shared_ptr<LabelVarLocation>(new LabelVarLocation(this->name));
            newVariable = new Variable(location, type, this->attributes.isFinal);

            std::string assemblyReserveString = "resb " + std::to_string(type->GetSize());
            DataDeclarationLine* dataDeclarationLine = new DataDeclarationLine(this->name, assemblyReserveString);
            assemblyCode->AddToBss(dataDeclarationLine);
        }
        // inline or data/rodata
        else
        {
            std::shared_ptr<Variable> value = this->value->TraverseExpression(codeGenerator, assemblyCode);

            if (!value->IsInline())
            {
                Logger.Log("Cannot assign a non-inline value to a global variable in global scope", Logger::ERROR);
                return;
            }

            if (value->type != type)
            {
                Logger.Log("Assign types of global variable " + this->name + " don't match", Logger::ERROR);
                return;
            }

            // inline
            if (this->attributes.isInline)
            {
                newVariable = new Variable(value->location, type, this->attributes.isFinal);
            }
            // data/rodata
            else
            {
                std::shared_ptr<LabelVarLocation> location = std::shared_ptr<LabelVarLocation>(new LabelVarLocation(this->name));
                newVariable = new Variable(location, type, this->attributes.isFinal);

                std::string assemblyDefineString = type->GetAssemblyDefineString() + " ";

                if (value == nullptr || value->location == nullptr)
                {
                    assemblyDefineString += "VALUE OR VALUE->LOCATION IS NULLPTR";
                }
                else
                {
                    assemblyDefineString += value->location->ToAssemblyDefineString();
                }

                DataDeclarationLine* dataDeclarationLine = new DataDeclarationLine(this->name, assemblyDefineString);

                if (this->attributes.isFinal)
                {
                    assemblyCode->AddToRoData(dataDeclarationLine);
                }
                else
                {
                    assemblyCode->AddToData(dataDeclarationLine);
                }
            }
        }

        codeGenerator->AddVariable(this->name, std::shared_ptr<Variable>(newVariable));
    }

    virtual std::string ToString() override { return "global " + AbstractVarDeclarationNode::ToString(); }
};