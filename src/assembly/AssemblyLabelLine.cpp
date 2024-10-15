#pragma once

#include "IAssemblyLine.cpp"

class AssemblyLabelLine : public IAssemblyLine
{
   public:
    AssemblyLabelLine(std::string label) { this->label = label; };
    virtual ~AssemblyLabelLine() = default;

    std::string ToString() override { return label + ":"; };

   private:
    std::string label;
};