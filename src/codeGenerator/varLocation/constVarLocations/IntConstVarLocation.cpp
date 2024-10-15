#pragma once

#include "../../../utils/Logger.cpp"
#include "BoolConstVarLocation.cpp"
#include "IConstVarLocation.cpp"

class IntConstVarLocation : public IConstVarLocation
{
   private:
    int value;

   public:
    IntConstVarLocation(int value) { this->value = value; }

    /// @brief Returns wheter the value is a multiple of 2
    /// @param power If not nullptr, is set so that 2^power will be the value
    bool IsMultipleOfTwo(unsigned int* power = nullptr)
    {
        // If the value is odd immediately return false
        if (value & 1) return false;

        if (power == nullptr) return true;

        // Calculate the power of 2
        *power = 1;
        int temp = value / 2;

        while (temp % 2 == 0)
        {
            temp /= 2;
            (*power)++;
        }

        return true;
    }

    virtual IVariableLocation* Clone() override { return new IntConstVarLocation(value); }

    virtual std::string ToAssemblyString() override { return std::to_string(value); }
    virtual std::string ToAssemblyDefineString() override { return std::to_string(value); }

    virtual IConstVarLocation* GenerateAdd(IConstVarLocation* source) override
    {
        IntConstVarLocation* intSource = dynamic_cast<IntConstVarLocation*>(source);

        if (intSource == nullptr)
        {
            Logger.Log("Cannot add inline non-integer to inline integer", Logger::ERROR);
            return nullptr;
        }

        return new IntConstVarLocation(value + intSource->value);
    }
    virtual IConstVarLocation* GenerateSub(IConstVarLocation* source) override
    {
        IntConstVarLocation* intSource = dynamic_cast<IntConstVarLocation*>(source);

        if (intSource == nullptr)
        {
            Logger.Log("Cannot subtract inline non-integer from inline integer", Logger::ERROR);
            return nullptr;
        }

        return new IntConstVarLocation(value - intSource->value);
    }
    virtual IConstVarLocation* GenerateMul(IConstVarLocation* source) override
    {
        IntConstVarLocation* intSource = dynamic_cast<IntConstVarLocation*>(source);

        if (intSource == nullptr)
        {
            Logger.Log("Cannot multiply inline non-integer with inline integer", Logger::ERROR);
            return nullptr;
        }

        return new IntConstVarLocation(value * intSource->value);
    }
    virtual IConstVarLocation* GenerateDiv(IConstVarLocation* source) override
    {
        IntConstVarLocation* intSource = dynamic_cast<IntConstVarLocation*>(source);

        if (intSource == nullptr)
        {
            Logger.Log("Cannot divide inline integer by inline non-integer", Logger::ERROR);
            return nullptr;
        }

        if (intSource->value == 0)
        {
            Logger.Log("Cannot divide by zero", Logger::ERROR);
            return nullptr;
        }

        return new IntConstVarLocation(value / intSource->value);
    }
    virtual IConstVarLocation* GenerateMod(IConstVarLocation* source) override
    {
        IntConstVarLocation* intSource = dynamic_cast<IntConstVarLocation*>(source);

        if (intSource == nullptr)
        {
            Logger.Log("Cannot modulo inline integer by inline non-integer", Logger::ERROR);
            return nullptr;
        }

        return new IntConstVarLocation(value % intSource->value);
    }

    virtual IConstVarLocation* GenerateAnd(IConstVarLocation* source) override
    {
        IntConstVarLocation* intSource = dynamic_cast<IntConstVarLocation*>(source);

        if (intSource == nullptr)
        {
            Logger.Log("Cannot AND inline integer with inline non-integer", Logger::ERROR);
            return nullptr;
        }

        return new IntConstVarLocation(value & intSource->value);
    }
    virtual IConstVarLocation* GenerateOr(IConstVarLocation* source) override
    {
        IntConstVarLocation* intSource = dynamic_cast<IntConstVarLocation*>(source);

        if (intSource == nullptr)
        {
            Logger.Log("Cannot OR inline integer with inline non-integer", Logger::ERROR);
            return nullptr;
        }

        return new IntConstVarLocation(value | intSource->value);
    }

    virtual IConstVarLocation* GenerateEqual(IConstVarLocation* source) override
    {
        IntConstVarLocation* intSource = dynamic_cast<IntConstVarLocation*>(source);

        if (intSource == nullptr)
        {
            Logger.Log("Cannot compare inline integer with inline non-integer", Logger::ERROR);
            return nullptr;
        }

        return new BoolConstVarLocation(value == intSource->value);
    }
    virtual IConstVarLocation* GenerateNotEqual(IConstVarLocation* source) override
    {
        IntConstVarLocation* intSource = dynamic_cast<IntConstVarLocation*>(source);

        if (intSource == nullptr)
        {
            Logger.Log("Cannot compare inline integer with inline non-integer", Logger::ERROR);
            return nullptr;
        }

        return new BoolConstVarLocation(value != intSource->value);
    }
    virtual IConstVarLocation* GenerateLess(IConstVarLocation* source) override
    {
        IntConstVarLocation* intSource = dynamic_cast<IntConstVarLocation*>(source);

        if (intSource == nullptr)
        {
            Logger.Log("Cannot compare inline integer with inline non-integer", Logger::ERROR);
            return nullptr;
        }

        return new BoolConstVarLocation(value < intSource->value);
    }
    virtual IConstVarLocation* GenerateLessEqual(IConstVarLocation* source) override
    {
        IntConstVarLocation* intSource = dynamic_cast<IntConstVarLocation*>(source);

        if (intSource == nullptr)
        {
            Logger.Log("Cannot compare inline integer with inline non-integer", Logger::ERROR);
            return nullptr;
        }

        return new BoolConstVarLocation(value <= intSource->value);
    }
    virtual IConstVarLocation* GenerateGreater(IConstVarLocation* source) override
    {
        IntConstVarLocation* intSource = dynamic_cast<IntConstVarLocation*>(source);

        if (intSource == nullptr)
        {
            Logger.Log("Cannot compare inline integer with inline non-integer", Logger::ERROR);
            return nullptr;
        }

        return new BoolConstVarLocation(value > intSource->value);
    }
    virtual IConstVarLocation* GenerateGreaterEqual(IConstVarLocation* source) override
    {
        IntConstVarLocation* intSource = dynamic_cast<IntConstVarLocation*>(source);

        if (intSource == nullptr)
        {
            Logger.Log("Cannot compare inline integer with inline non-integer", Logger::ERROR);
            return nullptr;
        }

        return new BoolConstVarLocation(value >= intSource->value);
    }

    virtual IConstVarLocation* GenerateNot() override { return new IntConstVarLocation(~value); }
    virtual IConstVarLocation* GenerateNeg() override { return new IntConstVarLocation(-value); }
    virtual IConstVarLocation* GenerateInc() override { return new IntConstVarLocation(value + 1); }
    virtual IConstVarLocation* GenerateDec() override { return new IntConstVarLocation(value - 1); }

    virtual bool IsZero() override { return value == 0; }
};