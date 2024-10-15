#pragma once

#include "../AbstractTreeNode.cpp"

class AbstractLineNode : public AbstractTreeNode
{
   public:
    AbstractLineNode();
    virtual ~AbstractLineNode();
};

AbstractLineNode::AbstractLineNode() : AbstractTreeNode() {}

AbstractLineNode::~AbstractLineNode() {}