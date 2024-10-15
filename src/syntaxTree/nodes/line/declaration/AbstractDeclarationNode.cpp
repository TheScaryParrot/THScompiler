#pragma once

#include "../AbstractLineNode.cpp"

class AbstractDeclarationNode : public AbstractLineNode
{
   public:
    AbstractDeclarationNode();
};

AbstractDeclarationNode::AbstractDeclarationNode() : AbstractLineNode() {}