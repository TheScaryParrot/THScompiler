#pragma once

#include <string>

class IVariableLocation
{
   public:
    virtual bool IsInline() = 0;

    virtual IVariableLocation* Clone() = 0;

    virtual std::string ToAssemblyString() = 0;
    /// @brief Retuns the string used to define the variable in the assembly code
    virtual std::string ToAssemblyDefineString() = 0;

    /// @brief Whether a register is required as intermediate storage for the variable when trying to do operations on it (eg. memory dereference)
    virtual bool RequiresRegister() = 0;

    /// @brief Whether this location requires a size keyword in the assembly code (eg. DWORD [rbp+1])
    virtual bool RequiresSizeKeyword() = 0;

    ///@brief Whether this location is a register
    virtual bool IsRegister() { return false; };
};