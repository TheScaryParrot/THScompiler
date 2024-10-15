#pragma once

#include "AbstractConstValueNode.cpp"

class FloatConstValueNode : public AbstractConstValueNode
{
   public:
    FloatConstValueNode(float value) : AbstractConstValueNode() { this->value = value; }

    float GetValue() { return this->value; };

    virtual std::shared_ptr<Variable> TraverseExpression(CodeGenerator* codeGenerator, AssemblyCode* assemblyCode) override
    {
        std::shared_ptr<Type> type = codeGenerator->GetType("float");
        IVariableLocation* location = new FloatConstVarLocation(value);
        return std::shared_ptr<Variable>(new Variable(std::shared_ptr<IVariableLocation>(location), type, true));
    }

    virtual std::string ToString() override { return std::to_string(GetValue()); }

   private:
    float value;
};