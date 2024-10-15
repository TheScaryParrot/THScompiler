#pragma once

#include "../../../assembly/AssemblyInstructionLine.cpp"
#include "PrimitiveType.cpp"

class FloatType : public PrimitiveType
{
    virtual void GenerateMod(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot mod two floats", Logger::ERROR);
    }

    virtual unsigned int GetSize() override { return 4; }
};