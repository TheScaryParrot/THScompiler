#pragma once

#include "../AbstractLineNode.cpp"

class AbstractStatementNode : public AbstractLineNode
{
   public:
    AbstractStatementNode();
    virtual ~AbstractStatementNode();
};

AbstractStatementNode::AbstractStatementNode() : AbstractLineNode() {}

AbstractStatementNode::~AbstractStatementNode() {}
