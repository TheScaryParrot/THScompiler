#pragma once

#include <string>

#include "../../assembly/AssemblyCode.cpp"
#include "../../codeGenerator/CodeGenerator.cpp"

class AbstractTreeNode
{
   public:
    virtual std::string ToString() = 0;

    virtual void Traverse(CodeGenerator* codeGenerator, AssemblyCode* assemblyCode) = 0;
};