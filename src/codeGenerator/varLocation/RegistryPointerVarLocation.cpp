#pragma once

#include "../../utils/Logger.cpp"
#include "IVariableLocation.cpp"

class RegistryPointerVarLocation : public IVariableLocation
{
   private:
    std::string registry;
    int offset;

   public:
    RegistryPointerVarLocation(std::string registry, int offset)
    {
        this->registry = registry;
        this->offset = offset;
    }

    std::string GetRegistry() { return registry; }
    void SetRegistry(std::string registry) { this->registry = registry; }

    int GetOffset() { return offset; }
    void SetOffset(int offset) { this->offset = offset; }
    /// @brief Adds increment to the offset; increment can be negative
    void IncrementOffset(int increment) { offset += increment; }

    virtual bool IsInline() override { return false; }

    virtual IVariableLocation* Clone() override { return new RegistryPointerVarLocation(registry, offset); }

    virtual std::string ToAssemblyString() override
    {
        std::string result = "[" + registry;

        if (offset == 0)
        {
            return result + "]";
        }

        if (offset > 0)
        {
            result += "+";
        }

        return result + std::to_string(offset) + "]";
    }

    virtual std::string ToAssemblyDefineString() override
    {
        Logger.Log("Cannot define RegistryPointerVarLocation in assembly code", Logger::ERROR);
        return "";
    }

    virtual bool RequiresRegister() override { return true; }
    virtual bool RequiresSizeKeyword() override { return true; }
};