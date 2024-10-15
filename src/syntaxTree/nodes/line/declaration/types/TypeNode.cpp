#pragma once

#include "../../../AbstractTreeNode.cpp"

class TypeNode : public AbstractTreeNode
{
   public:
    TypeNode(std::string name);
    TypeNode() = default;
    ~TypeNode();

    virtual void Traverse(CodeGenerator* codeGenerator, AssemblyCode* assemblyCode) override
    {
        Logger.Log("TypeNode::Traverse() is not suposed to be called. Use name property directly", Logger::ERROR);
    }

    virtual std::string ToString() override;

    std::string name;
};

TypeNode::TypeNode(std::string name) : AbstractTreeNode() { this->name = name; }

TypeNode::~TypeNode() {}

std::string TypeNode::ToString() { return name; }