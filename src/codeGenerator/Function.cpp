#pragma once

#include <memory>
#include <vector>

#include "types/Type.cpp"

class Function
{
   private:
    std::string label;

   public:
    std::vector<std::shared_ptr<Type>> parameterTypes;
    std::shared_ptr<Type> returnType;

    Function(std::string label, std::vector<std::shared_ptr<Type>> parameterTypes, std::shared_ptr<Type> returnType)
    {
        this->label = label;
        this->parameterTypes = parameterTypes;
        this->returnType = returnType;
    }

    void GenerateCallInstruction(AssemblyCode* assemblyCode)
    {
        AssemblyInstructionLine* line = new AssemblyInstructionLine("call");
        line->AddArgument(label);
        assemblyCode->AddLine(line);
    }
};