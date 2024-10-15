#pragma once

#include "../../../assembly/AssemblyInstructionLine.cpp"
#include "PrimitiveType.cpp"

class IntType : public PrimitiveType
{
    virtual unsigned int GetSize() override { return 4; }
};