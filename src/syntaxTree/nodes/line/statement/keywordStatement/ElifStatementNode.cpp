#pragma once

#include "../../expression/AbstractExpressionNode.cpp"
#include "AbstractKeywordStatementNode.cpp"

class ElifStatementNode : public AbstractKeywordStatementNode
{
   public:
    ElifStatementNode(AbstractExpressionNode* expression, AbstractStatementNode* statement);
    ~ElifStatementNode();

    virtual void Traverse(CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
    {
        Logger.Log("ElifStatementNode::Traverse() is not supposed to be used. Use expression and statement properties instead.", Logger::ERROR);
    }

    virtual std::string ToString() override;

    AbstractExpressionNode* expression;
    AbstractStatementNode* statement;
};

ElifStatementNode::ElifStatementNode(AbstractExpressionNode* expression, AbstractStatementNode* statement) : AbstractKeywordStatementNode()
{
    this->expression = expression;
    this->statement = statement;
}

ElifStatementNode::~ElifStatementNode()
{
    delete expression;
    delete statement;
}

std::string ElifStatementNode::ToString() { return "elif (" + expression->ToString() + ")\n" + statement->ToString(); }