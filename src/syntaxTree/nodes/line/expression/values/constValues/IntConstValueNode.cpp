#pragma once

#include "AbstractConstValueNode.cpp"

class IntConstValueNode : public AbstractConstValueNode
{
   public:
    IntConstValueNode(int value) : AbstractConstValueNode() { this->value = value; }

    int GetValue() { return this->value; }

    virtual std::shared_ptr<Variable> TraverseExpression(CodeGenerator* codeGenerator, AssemblyCode* assemblyCode) override
    {
        std::shared_ptr<Type> type = codeGenerator->GetType("int");
        IVariableLocation* location = new IntConstVarLocation(value);
        return std::shared_ptr<Variable>(new Variable(std::shared_ptr<IVariableLocation>(location), type, true));
    }

    virtual std::string ToString() override { return std::to_string(GetValue()); }

   private:
    int value;
};