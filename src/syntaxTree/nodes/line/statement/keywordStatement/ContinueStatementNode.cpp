#pragma once

#include "AbstractKeywordStatementNode.cpp"

class ContinueStatementNode : public AbstractKeywordStatementNode
{
   public:
    virtual void Traverse(CodeGenerator* codeGenerator, AssemblyCode* assemblyCode) override
    {
        assemblyCode->AddLine(new AssemblyInstructionLine("jmp " + codeGenerator->GetContinueLabel()));
    }

    virtual std::string ToString() override { return "continue"; }
};