#pragma once

#include "AbstractKeywordStatementNode.cpp"

class BreakStatementNode : public AbstractKeywordStatementNode
{
   public:
    virtual void Traverse(CodeGenerator* codeGenerator, AssemblyCode* assemblyCode) override
    {
        assemblyCode->AddLine(new AssemblyInstructionLine("jmp " + codeGenerator->GetBreakLabel()));
    }

    virtual std::string ToString() override { return "break"; }
};