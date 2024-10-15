#pragma once

#include "AbstractConstValueNode.cpp"

class LogicalConstValueNode : public AbstractConstValueNode
{
   public:
    LogicalConstValueNode(bool value) : AbstractConstValueNode() { this->value = value; };

    bool GetValue() { return value; };

    virtual std::shared_ptr<Variable> TraverseExpression(CodeGenerator* codeGenerator, AssemblyCode* assemblyCode) override
    {
        std::shared_ptr<Type> type = codeGenerator->GetType("bool");
        IVariableLocation* location = new BoolConstVarLocation(value);
        return std::shared_ptr<Variable>(new Variable(std::shared_ptr<IVariableLocation>(location), type, true));
    }

    virtual std::string ToString() override { return value ? "true" : "false"; };

   private:
    bool value;
};