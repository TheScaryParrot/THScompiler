#pragma once

#include <string>
#include <vector>

#include "IAssemblyLine.cpp"

class AssemblyInstructionLine : public IAssemblyLine
{
   public:
    AssemblyInstructionLine(std::string instruction) { this->instruction = instruction; };
    virtual ~AssemblyInstructionLine() = default;

    void AddArgument(std::string argument) { arguments.push_back(argument); }

    virtual std::string ToString() override
    {
        std::string result = instruction + " ";

        if (arguments.size() <= 0) return result;

        result += arguments.front();

        for (size_t i = 1; i < arguments.size(); i++)
        {
            result += ", " + arguments[i];
        }

        return result;
    }

   private:
    std::string instruction;
    std::vector<std::string> arguments;
};