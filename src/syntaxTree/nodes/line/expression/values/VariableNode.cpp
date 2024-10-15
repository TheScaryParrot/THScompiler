#pragma once

#include <vector>

#include "AbstractValueNode.cpp"

class VariableNode : public AbstractValueNode
{
   public:
    VariableNode(std::vector<std::string> ids) { this->ids = ids; }

    virtual bool RequiresAXRegister() override { return false; }

    virtual std::shared_ptr<Variable> TraverseExpression(CodeGenerator* codeGenerator, AssemblyCode* assemblyCode) override
    {
        if (this->ids.size() == 0)
        {
            Logger.Log("VariableNode with no ids. This is a mistake of the idiot who made this compiler", Logger::ERROR);
            return nullptr;
        }

        if (!codeGenerator->DoesVariableExist(this->ids[0]))
        {
            Logger.Log("Variable " + this->ids[0] + " does not exist", Logger::ERROR);
            return nullptr;
        }

        std::shared_ptr<Variable> variable = codeGenerator->GetVariable(this->ids[0]);

        for (size_t i = 1; i < this->ids.size(); i++)
        {
            StructType* structType = dynamic_cast<StructType*>(variable->type.get());

            if (structType == nullptr)
            {
                Logger.Log("Cannot access property as " + this->ids[i] + " is not a struct", Logger::ERROR);
                return nullptr;
            }

            variable = structType->GetProperty(this->ids[i], variable->location);
        }

        return variable;
    }

    virtual std::string ToString() override
    {
        std::string result = ids[0];

        for (size_t i = 1; i < ids.size(); i++)
        {
            result += "." + ids[i];
        }

        return result;
    }

    std::vector<std::string> ids;
};