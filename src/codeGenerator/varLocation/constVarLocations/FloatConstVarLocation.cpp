#pragma once

#include "../../../utils/Logger.cpp"
#include "BoolConstVarLocation.cpp"
#include "IConstVarLocation.cpp"

class FloatConstVarLocation : public IConstVarLocation
{
   private:
    float value;

   public:
    FloatConstVarLocation(float value) { this->value = value; }

    virtual IVariableLocation* Clone() override { return new FloatConstVarLocation(value); };

    virtual std::string ToAssemblyString() override { return "__float32__(" + std::to_string(value) + ")"; };
    virtual std::string ToAssemblyDefineString() override { return std::to_string(value); };

    virtual IConstVarLocation* GenerateAdd(IConstVarLocation* source) override
    {
        FloatConstVarLocation* floatSource = dynamic_cast<FloatConstVarLocation*>(source);

        if (floatSource == nullptr)
        {
            Logger.Log("Cannot add inline non-float to inline float", Logger::ERROR);
            return nullptr;
        }

        return new FloatConstVarLocation(value + floatSource->value);
    }
    virtual IConstVarLocation* GenerateSub(IConstVarLocation* source) override
    {
        FloatConstVarLocation* floatSource = dynamic_cast<FloatConstVarLocation*>(source);

        if (floatSource == nullptr)
        {
            Logger.Log("Cannot subtract inline non-float from inline float", Logger::ERROR);
            return nullptr;
        }

        return new FloatConstVarLocation(value - floatSource->value);
    }
    virtual IConstVarLocation* GenerateMul(IConstVarLocation* source) override
    {
        FloatConstVarLocation* floatSource = dynamic_cast<FloatConstVarLocation*>(source);

        if (floatSource == nullptr)
        {
            Logger.Log("Cannot multiply inline non-float with inline float", Logger::ERROR);
            return nullptr;
        }

        return new FloatConstVarLocation(value * floatSource->value);
    }
    virtual IConstVarLocation* GenerateDiv(IConstVarLocation* source) override
    {
        FloatConstVarLocation* floatSource = dynamic_cast<FloatConstVarLocation*>(source);

        if (floatSource == nullptr)
        {
            Logger.Log("Cannot divide inline float by inline non-float", Logger::ERROR);
            return nullptr;
        }

        return new FloatConstVarLocation(value / floatSource->value);
    }
    virtual IConstVarLocation* GenerateMod(IConstVarLocation* source) override
    {
        Logger.Log("Cannot modulo inline float by inline float", Logger::ERROR);
        return nullptr;
    }

    virtual IConstVarLocation* GenerateAnd(IConstVarLocation* source) override
    {
        Logger.Log("Cannot AND inline float with inline float", Logger::ERROR);
        return nullptr;
    }
    virtual IConstVarLocation* GenerateOr(IConstVarLocation* source) override
    {
        Logger.Log("Cannot OR inline float with inline float", Logger::ERROR);
        return nullptr;
    }

    virtual IConstVarLocation* GenerateEqual(IConstVarLocation* source) override
    {
        FloatConstVarLocation* floatSource = dynamic_cast<FloatConstVarLocation*>(source);

        if (floatSource == nullptr)
        {
            Logger.Log("Cannot compare inline float with inline non-float", Logger::ERROR);
            return nullptr;
        }

        return new BoolConstVarLocation(value == floatSource->value);
    }
    virtual IConstVarLocation* GenerateNotEqual(IConstVarLocation* source) override
    {
        FloatConstVarLocation* floatSource = dynamic_cast<FloatConstVarLocation*>(source);

        if (floatSource == nullptr)
        {
            Logger.Log("Cannot compare inline float with inline non-float", Logger::ERROR);
            return nullptr;
        }

        return new BoolConstVarLocation(value != floatSource->value);
    }
    virtual IConstVarLocation* GenerateLess(IConstVarLocation* source) override
    {
        FloatConstVarLocation* floatSource = dynamic_cast<FloatConstVarLocation*>(source);

        if (floatSource == nullptr)
        {
            Logger.Log("Cannot compare inline float with inline non-float", Logger::ERROR);
            return nullptr;
        }

        return new BoolConstVarLocation(value < floatSource->value);
    }
    virtual IConstVarLocation* GenerateLessEqual(IConstVarLocation* source) override
    {
        FloatConstVarLocation* floatSource = dynamic_cast<FloatConstVarLocation*>(source);

        if (floatSource == nullptr)
        {
            Logger.Log("Cannot compare inline float with inline non-float", Logger::ERROR);
            return nullptr;
        }

        return new BoolConstVarLocation(value <= floatSource->value);
    }
    virtual IConstVarLocation* GenerateGreater(IConstVarLocation* source) override
    {
        FloatConstVarLocation* floatSource = dynamic_cast<FloatConstVarLocation*>(source);

        if (floatSource == nullptr)
        {
            Logger.Log("Cannot compare inline float with inline non-float", Logger::ERROR);
            return nullptr;
        }

        return new BoolConstVarLocation(value > floatSource->value);
    }
    virtual IConstVarLocation* GenerateGreaterEqual(IConstVarLocation* source) override
    {
        FloatConstVarLocation* floatSource = dynamic_cast<FloatConstVarLocation*>(source);

        if (floatSource == nullptr)
        {
            Logger.Log("Cannot compare inline float with inline non-float", Logger::ERROR);
            return nullptr;
        }

        return new BoolConstVarLocation(value >= floatSource->value);
    }

    virtual IConstVarLocation* GenerateNot() override
    {
        Logger.Log("Cannot NOT inline float", Logger::ERROR);
        return nullptr;
    }
    virtual IConstVarLocation* GenerateNeg() override { return new FloatConstVarLocation(-value); }
    virtual IConstVarLocation* GenerateInc() override
    {
        Logger.Log("Cannot increment inline float", Logger::ERROR);
        return nullptr;
    }
    virtual IConstVarLocation* GenerateDec() override
    {
        Logger.Log("Cannot decrement inline float", Logger::ERROR);
        return nullptr;
    }

    virtual bool IsZero() override { return value == 0; };
};