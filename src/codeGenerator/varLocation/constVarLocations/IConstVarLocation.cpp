#pragma once

#include "../IVariableLocation.cpp"

/// @brief Interface for constant variable locations (eg 5) Allows for operation evaluation at compile time.
class IConstVarLocation : public IVariableLocation
{
   public:
    virtual bool IsInline() override { return true; };
    virtual bool RequiresRegister() override { return true; };
    virtual bool RequiresSizeKeyword() override { return false; };

    virtual IConstVarLocation* GenerateAdd(IConstVarLocation* source) = 0;
    virtual IConstVarLocation* GenerateSub(IConstVarLocation* source) = 0;
    virtual IConstVarLocation* GenerateMul(IConstVarLocation* source) = 0;
    virtual IConstVarLocation* GenerateDiv(IConstVarLocation* source) = 0;
    virtual IConstVarLocation* GenerateMod(IConstVarLocation* source) = 0;

    virtual IConstVarLocation* GenerateAnd(IConstVarLocation* source) = 0;
    virtual IConstVarLocation* GenerateOr(IConstVarLocation* source) = 0;

    virtual IConstVarLocation* GenerateEqual(IConstVarLocation* source) = 0;
    virtual IConstVarLocation* GenerateNotEqual(IConstVarLocation* source) = 0;
    virtual IConstVarLocation* GenerateLess(IConstVarLocation* source) = 0;
    virtual IConstVarLocation* GenerateLessEqual(IConstVarLocation* source) = 0;
    virtual IConstVarLocation* GenerateGreater(IConstVarLocation* source) = 0;
    virtual IConstVarLocation* GenerateGreaterEqual(IConstVarLocation* source) = 0;

    virtual IConstVarLocation* GenerateNot() = 0;
    virtual IConstVarLocation* GenerateNeg() = 0;
    virtual IConstVarLocation* GenerateInc() = 0;
    virtual IConstVarLocation* GenerateDec() = 0;

    /// @brief Returns whether the constant is zero. Used for optimizing useless operations (eg. if false)
    virtual bool IsZero() = 0;
};