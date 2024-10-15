#pragma once

#include "AbstractCompilerInstructionNode.cpp"

class GlobalInstructionNode : public AbstractCompilerInstructionNode
{
   public:
    std::string identifier;

    GlobalInstructionNode(std::string identifier) : AbstractCompilerInstructionNode() { this->identifier = identifier; }

    virtual void Traverse(CodeGenerator* codeGenerator, AssemblyCode* assemblyCode) override
    {
        AssemblyInstructionLine* globalLine = new AssemblyInstructionLine("global");
        globalLine->AddArgument(this->identifier);
        assemblyCode->AddLine(globalLine);
    }

    virtual std::string ToString() override { return "global " + identifier; }
};