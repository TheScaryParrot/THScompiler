#pragma once

#include "../AbstractStatementNode.cpp"

class AbstractKeywordStatementNode : public AbstractStatementNode
{
   public:
    AbstractKeywordStatementNode();
    virtual ~AbstractKeywordStatementNode();
};

AbstractKeywordStatementNode::AbstractKeywordStatementNode() : AbstractStatementNode() {}

AbstractKeywordStatementNode::~AbstractKeywordStatementNode() {}