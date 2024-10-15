#pragma once

#include "AbstractStatementNode.cpp"

class EmptyStatementNode : public AbstractStatementNode
{
   public:
    virtual void Traverse(CodeGenerator* codeGenerator, AssemblyCode* assemblyCode) override { /* Do nothing */ }

    virtual std::string ToString() override { return ";"; }
};