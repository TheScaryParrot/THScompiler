#pragma once

#include "../../utils/Logger.cpp"
#include "IVariableLocation.cpp"

class RegisterVarLocation : public IVariableLocation
{
   private:
    std::string registry;

   public:
    RegisterVarLocation(std::string registry) { this->registry = registry; }

    virtual bool IsInline() override { return false; }

    virtual IVariableLocation* Clone() override { return new RegisterVarLocation(registry); }

    virtual std::string ToAssemblyString() override { return registry; }
    /// @brief Retuns the string used to define the variable in the assembly code
    virtual std::string ToAssemblyDefineString() override
    {
        Logger.Log("Cannot define RegisterVarLocation in assembly code", Logger::ERROR);
        return "";
    }

    virtual bool RequiresRegister() override { return false; }
    virtual bool RequiresSizeKeyword() override { return false; }
    virtual bool IsRegister() override { return true; }
};