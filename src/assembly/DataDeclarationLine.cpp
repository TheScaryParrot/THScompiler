#pragma once

#include "IAssemblyLine.cpp"

class DataDeclarationLine : public IAssemblyLine
{
   public:
    DataDeclarationLine(std::string label, std::string assignment)
    {
        this->label = label;
        this->assignment = assignment;
    }
    virtual ~DataDeclarationLine() = default;

    virtual std::string ToString() override { return label + ": " + assignment; }

   private:
    std::string label;
    std::string assignment;
};