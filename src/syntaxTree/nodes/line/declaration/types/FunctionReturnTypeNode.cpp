#pragma once

#include "TypeNode.cpp"

class FunctionReturnTypeNode : public TypeNode
{
   public:
    FunctionReturnTypeNode(std::string name);
    FunctionReturnTypeNode() = default;
    ~FunctionReturnTypeNode();

    virtual std::string ToString() override;

    bool IsVoid();
};

FunctionReturnTypeNode::FunctionReturnTypeNode(std::string name) : TypeNode(name) {}

FunctionReturnTypeNode::~FunctionReturnTypeNode() {}

bool FunctionReturnTypeNode::IsVoid() { return name == "void"; }

std::string FunctionReturnTypeNode::ToString() { return name; }