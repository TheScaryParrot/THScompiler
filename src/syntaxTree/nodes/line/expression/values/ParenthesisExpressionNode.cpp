#pragma once

#include "AbstractValueNode.cpp"

class ParenthesisExpressionNode : public AbstractValueNode
{
   public:
    AbstractExpressionNode* expression;

    ParenthesisExpressionNode(AbstractExpressionNode* expression) : AbstractValueNode() { this->expression = expression; }

    ~ParenthesisExpressionNode() { delete expression; }

    virtual bool RequiresAXRegister() override { return expression->RequiresAXRegister(); }

    virtual std::shared_ptr<Variable> TraverseExpression(CodeGenerator* codeGenerator, AssemblyCode* assemblyCode) override
    {
        return expression->TraverseExpression(codeGenerator, assemblyCode);
    }

    virtual std::string ToString() override { return "(" + expression->ToString() + ")"; }
};
