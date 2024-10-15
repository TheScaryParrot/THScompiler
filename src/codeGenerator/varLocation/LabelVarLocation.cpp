#pragma once

#include "../../utils/Logger.cpp"
#include "IVariableLocation.cpp"

class LabelVarLocation : public IVariableLocation
{
   private:
    std::string label;

   public:
    LabelVarLocation(std::string label) { this->label = label; }

    virtual bool IsInline() override { return false; }

    virtual IVariableLocation* Clone() override { return new LabelVarLocation(label); }

    virtual std::string ToAssemblyString() override { return "[" + label + "]"; }

    virtual std::string ToAssemblyDefineString() override
    {
        Logger.Log("Cannot define LabelVarLocation in assembly code", Logger::ERROR);
        return "";
    }

    virtual bool RequiresRegister() override { return true; }
    virtual bool RequiresSizeKeyword() override { return true; }
};