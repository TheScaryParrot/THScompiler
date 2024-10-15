#pragma once

#include "../../../utils/Logger.cpp"
#include "IConstVarLocation.cpp"

class BoolConstVarLocation : public IConstVarLocation
{
   private:
    bool value;

   public:
    BoolConstVarLocation(bool value) { this->value = value; }

    virtual IVariableLocation* Clone() override { return new BoolConstVarLocation(value); };

    virtual std::string ToAssemblyString() override { return std::to_string(value); };
    virtual std::string ToAssemblyDefineString() override { return std::to_string(value); };

    virtual IConstVarLocation* GenerateAdd(IConstVarLocation* source) override
    {
        Logger.Log("Cannot add inline bool with inline bool", Logger::ERROR);
        return nullptr;
    }
    virtual IConstVarLocation* GenerateSub(IConstVarLocation* source) override
    {
        Logger.Log("Cannot subtract inline bool from inline bool", Logger::ERROR);
        return nullptr;
    }
    virtual IConstVarLocation* GenerateMul(IConstVarLocation* source) override
    {
        Logger.Log("Cannot multiply inline bool with inline bool", Logger::ERROR);
        return nullptr;
    }
    virtual IConstVarLocation* GenerateDiv(IConstVarLocation* source) override
    {
        Logger.Log("Cannot divide inline bool by inline bool", Logger::ERROR);
        return nullptr;
    }
    virtual IConstVarLocation* GenerateMod(IConstVarLocation* source) override
    {
        Logger.Log("Cannot modulo inline bool by inline bool", Logger::ERROR);
        return nullptr;
    }

    virtual IConstVarLocation* GenerateAnd(IConstVarLocation* source) override
    {
        BoolConstVarLocation* boolSource = dynamic_cast<BoolConstVarLocation*>(source);

        if (boolSource == nullptr)
        {
            Logger.Log("Cannot AND inline bool with inline non-bool", Logger::ERROR);
            return nullptr;
        }

        return new BoolConstVarLocation(value && boolSource->value);
    }
    virtual IConstVarLocation* GenerateOr(IConstVarLocation* source) override
    {
        BoolConstVarLocation* boolSource = dynamic_cast<BoolConstVarLocation*>(source);

        if (boolSource == nullptr)
        {
            Logger.Log("Cannot OR inline bool with inline non-bool", Logger::ERROR);
            return nullptr;
        }

        return new BoolConstVarLocation(value || boolSource->value);
    }

    virtual IConstVarLocation* GenerateEqual(IConstVarLocation* source) override
    {
        BoolConstVarLocation* boolSource = dynamic_cast<BoolConstVarLocation*>(source);

        if (boolSource == nullptr)
        {
            Logger.Log("Cannot compare inline bool with inline non-bool", Logger::ERROR);
            return nullptr;
        }

        return new BoolConstVarLocation(value == boolSource->value);
    }
    virtual IConstVarLocation* GenerateNotEqual(IConstVarLocation* source) override
    {
        BoolConstVarLocation* boolSource = dynamic_cast<BoolConstVarLocation*>(source);

        if (boolSource == nullptr)
        {
            Logger.Log("Cannot compare inline bool with inline non-bool", Logger::ERROR);
            return nullptr;
        }

        return new BoolConstVarLocation(value != boolSource->value);
    }
    virtual IConstVarLocation* GenerateLess(IConstVarLocation* source) override
    {
        Logger.Log("Cannot compare inline bool with inline bool", Logger::ERROR);
        return nullptr;
    }
    virtual IConstVarLocation* GenerateLessEqual(IConstVarLocation* source) override
    {
        Logger.Log("Cannot compare inline bool with inline bool", Logger::ERROR);
        return nullptr;
    }
    virtual IConstVarLocation* GenerateGreater(IConstVarLocation* source) override
    {
        Logger.Log("Cannot compare inline bool with inline bool", Logger::ERROR);
        return nullptr;
    }
    virtual IConstVarLocation* GenerateGreaterEqual(IConstVarLocation* source) override
    {
        Logger.Log("Cannot compare inline bool with inline bool", Logger::ERROR);
        return nullptr;
    }

    virtual IConstVarLocation* GenerateNot() override { return new BoolConstVarLocation(!value); }
    virtual IConstVarLocation* GenerateNeg() override
    {
        Logger.Log("Cannot negate inline bool", Logger::ERROR);
        return nullptr;
    }
    virtual IConstVarLocation* GenerateInc() override
    {
        Logger.Log("Cannot increment inline bool", Logger::ERROR);
        return nullptr;
    }
    virtual IConstVarLocation* GenerateDec() override
    {
        Logger.Log("Cannot decrement inline bool", Logger::ERROR);
        return nullptr;
    }

    virtual bool IsZero() override { return !value; }
};