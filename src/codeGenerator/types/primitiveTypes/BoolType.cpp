#pragma once

#include "../../../assembly/AssemblyInstructionLine.cpp"
#include "PrimitiveType.cpp"

class BoolType : public PrimitiveType
{
    virtual void GenerateAdd(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot add two bools", Logger::ERROR);
    }
    virtual void GenerateSub(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot subtract two bools", Logger::ERROR);
    }
    virtual void GenerateMul(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot multiply two bools", Logger::ERROR);
    }
    virtual void GenerateDiv(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot divide two bools", Logger::ERROR);
    }
    virtual void GenerateMod(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot mod two bools", Logger::ERROR);
    }

    virtual void GenerateNeg(std::shared_ptr<IVariableLocation> destination, AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot negate a bool", Logger::ERROR);
    }
    virtual void GenerateInc(std::shared_ptr<IVariableLocation> destination, AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot increment a bool", Logger::ERROR);
    }
    virtual void GenerateDec(std::shared_ptr<IVariableLocation> destination, AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot decrement a bool", Logger::ERROR);
    }

    virtual unsigned int GetSize() override { return 1; }
};