#pragma once

#include "PrimitiveType.cpp"

class CharType : public PrimitiveType
{
    virtual void GenerateAssign(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                                AssemblyCode* assemblyCode) override
    {
        // TODO: Add mov instruction
    }

    virtual void GenerateAdd(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) override
    {
        // TODO: Add add instruction
    }

    virtual void GenerateSub(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) override
    {
        // TODO: Add sub instruction
    }

    virtual void GenerateMul(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) override
    {
        // TODO: Add mul instruction
    }

    virtual void GenerateDiv(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) override
    {
        // TODO: Add div instruction
    }

    virtual void GenerateMod(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) override
    {
        // TODO: Add mod instruction
    }

    virtual void GenerateNot(std::shared_ptr<IVariableLocation> destination, AssemblyCode* assemblyCode) override
    {
        // TODO: Add not instruction
    }

    virtual void GenerateNeg(std::shared_ptr<IVariableLocation> destination, AssemblyCode* assemblyCode) override
    {
        // TODO: Add neg instruction
    }

    virtual void GenerateInc(std::shared_ptr<IVariableLocation> destination, AssemblyCode* assemblyCode) override
    {
        // TODO: Add inc instruction
    }

    virtual void GenerateDec(std::shared_ptr<IVariableLocation> destination, AssemblyCode* assemblyCode) override
    {
        // TODO: Add dec instruction
    }

    virtual void GenerateAnd(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) override
    {
        // TODO: Add and instruction
    }

    virtual void GenerateOr(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                            AssemblyCode* assemblyCode) override
    {
        // TODO: Add or instruction
    }

    virtual void GenerateEqual(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                               AssemblyCode* assemblyCode) override
    {
        // TODO: Add equal instruction
    }

    virtual void GenerateNotEqual(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                                  AssemblyCode* assemblyCode) override
    {
        // TODO: Add not equal instruction
    }

    virtual void GenerateLess(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                              AssemblyCode* assemblyCode) override
    {
        // TODO: Add less instruction
    }

    virtual void GenerateLessEqual(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                                   AssemblyCode* assemblyCode) override
    {
        // TODO: Add less equal instruction
    }

    virtual void GenerateGreater(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                                 AssemblyCode* assemblyCode) override
    {
        // TODO: Add greater instruction
    }

    virtual void GenerateGreaterEqual(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                                      AssemblyCode* assemblyCode) override
    {
        // TODO: Add greater equal instruction
    }

    virtual unsigned int GetSize() override { return 1; }
};