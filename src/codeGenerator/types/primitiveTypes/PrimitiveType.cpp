#pragma once

#include "../../varLocation/constVarLocations/IntConstVarLocation.cpp"
#include "../Type.cpp"

class PrimitiveType : public Type
{
   public:
    virtual void GenerateAssign(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                                AssemblyCode* assemblyCode) override
    {
        // No need to generate assign if the locations are the same
        if (destination->ToAssemblyString() == source->ToAssemblyString()) return;

        GenerateUsualBinaryOperation(destination, source, "mov", assemblyCode);
    }

    virtual void GenerateAdd(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) override
    {
        GenerateUsualBinaryOperation(destination, source, "add", assemblyCode);
    }

    virtual void GenerateSub(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) override
    {
        GenerateUsualBinaryOperation(destination, source, "sub", assemblyCode);
    }

    virtual void GenerateMul(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) override
    {
        // If source is multiple of 2, we can use shift left instead of mul
        IntConstVarLocation* intSource = dynamic_cast<IntConstVarLocation*>(source.get());
        unsigned int power;
        if (intSource != nullptr && intSource->IsMultipleOfTwo(&power))
        {
            std::shared_ptr<IVariableLocation> axRegister = destination;
            // If the destination is not ax, we need to move it to ax first
            if (!destination->IsRegister())
            {
                std::shared_ptr<IVariableLocation> axRegister =
                    std::shared_ptr<IVariableLocation>(AssemblyCodeGenerator.GetNewAXRegisterVarLocation(this->GetSize(), assemblyCode));
                GenerateAssign(axRegister, destination, assemblyCode);
            }

            AssemblyInstructionLine* line = new AssemblyInstructionLine("shl");
            line->AddArgument(ConstructVarLocationAccess(destination));
            line->AddArgument(std::to_string(power));
            assemblyCode->AddLine(line);

            // Revert the destination if it was not ax
            if (!destination->IsRegister())
            {
                GenerateAssign(destination, axRegister, assemblyCode);
            }

            return;
        }

        GenerateBinaryOperationOnAXregister(destination, source, "mul", assemblyCode);
    }

    virtual void GenerateDiv(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) override
    {
        // If source is multiple of 2, we can use shift right instead of div
        IntConstVarLocation* intSource = dynamic_cast<IntConstVarLocation*>(source.get());
        unsigned int power;
        if (intSource != nullptr && intSource->IsMultipleOfTwo(&power))
        {
            std::shared_ptr<IVariableLocation> axRegister = destination;
            // If the destination is not ax, we need to move it to ax first
            if (!destination->IsRegister())
            {
                std::shared_ptr<IVariableLocation> axRegister =
                    std::shared_ptr<IVariableLocation>(AssemblyCodeGenerator.GetNewAXRegisterVarLocation(this->GetSize(), assemblyCode));
                GenerateAssign(axRegister, destination, assemblyCode);
            }

            AssemblyInstructionLine* line = new AssemblyInstructionLine("shr");
            line->AddArgument(ConstructVarLocationAccess(destination));
            line->AddArgument(std::to_string(power));
            assemblyCode->AddLine(line);

            // Revert the destination if it was not ax
            if (!destination->IsRegister())
            {
                GenerateAssign(destination, axRegister, assemblyCode);
            }

            return;
        }

        // As div uses rdx:rax as dividend, we need to reset rdx to 0
        AssemblyInstructionLine* resetRDX = new AssemblyInstructionLine("xor");
        resetRDX->AddArgument("rdx");
        resetRDX->AddArgument("rdx");
        assemblyCode->AddLine(resetRDX);
        // Make sure B register is used in case of source needing a register
        GenerateBinaryOperationOnAXregister(destination, source, "div", assemblyCode, true);
    }

    virtual void GenerateMod(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) override
    {
        // As div uses rdx:rax as dividend, we need to reset rdx to 0
        AssemblyInstructionLine* resetRDX = new AssemblyInstructionLine("xor");
        resetRDX->AddArgument("rdx");
        resetRDX->AddArgument("rdx");
        assemblyCode->AddLine(resetRDX);
        // If source needs a register save it in BX
        if (source->RequiresRegister())
        {
            source = AssignIVarLocationToRegister(source, assemblyCode, true);
        }

        // Move destination to AX register, as div uses rdx:rax as dividend
        std::shared_ptr<IVariableLocation> axRegister = destination;
        if (!destination->IsRegister())
        {
            axRegister = std::shared_ptr<IVariableLocation>(AssemblyCodeGenerator.GetNewAXRegisterVarLocation(this->GetSize(), assemblyCode));
            GenerateAssign(axRegister, destination, assemblyCode);
        }

        // generate div instruction
        GenerateUsualUnaryOperation(source, "div", assemblyCode);

        // Remainder of div instruction is stored in rdx, so move it to destination
        std::shared_ptr<IVariableLocation> dxRegister =
            std::shared_ptr<IVariableLocation>(AssemblyCodeGenerator.GetNewDXRegisterVarLocation(this->GetSize(), assemblyCode));
        GenerateAssign(destination, dxRegister, assemblyCode);
    }

    virtual void GenerateNot(std::shared_ptr<IVariableLocation> destination, AssemblyCode* assemblyCode) override
    {
        GenerateUsualUnaryOperation(destination, "not", assemblyCode);
    }

    virtual void GenerateNeg(std::shared_ptr<IVariableLocation> destination, AssemblyCode* assemblyCode) override
    {
        GenerateUsualUnaryOperation(destination, "neg", assemblyCode);
    }

    virtual void GenerateInc(std::shared_ptr<IVariableLocation> destination, AssemblyCode* assemblyCode) override
    {
        GenerateUsualUnaryOperation(destination, "inc", assemblyCode);
    }

    virtual void GenerateDec(std::shared_ptr<IVariableLocation> destination, AssemblyCode* assemblyCode) override
    {
        GenerateUsualUnaryOperation(destination, "dec", assemblyCode);
    }

    virtual void GenerateAnd(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) override
    {
        GenerateUsualBinaryOperation(destination, source, "and", assemblyCode);
    }

    virtual void GenerateOr(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                            AssemblyCode* assemblyCode) override
    {
        GenerateUsualBinaryOperation(destination, source, "or", assemblyCode);
    }

    virtual void GenerateEqual(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                               AssemblyCode* assemblyCode) override
    {
        GenerateComparison("e", destination, source, assemblyCode);
    }

    virtual void GenerateNotEqual(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                                  AssemblyCode* assemblyCode) override
    {
        GenerateComparison("ne", destination, source, assemblyCode);
    }

    virtual void GenerateLess(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                              AssemblyCode* assemblyCode) override
    {
        GenerateComparison("l", destination, source, assemblyCode);
    }

    virtual void GenerateLessEqual(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                                   AssemblyCode* assemblyCode) override
    {
        GenerateComparison("le", destination, source, assemblyCode);
    }

    virtual void GenerateGreater(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                                 AssemblyCode* assemblyCode) override
    {
        GenerateComparison("g", destination, source, assemblyCode);
    }

    virtual void GenerateGreaterEqual(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                                      AssemblyCode* assemblyCode) override
    {
        GenerateComparison("ge", destination, source, assemblyCode);
    }

    virtual void GenerateStackPush(std::shared_ptr<IVariableLocation> source, AssemblyCode* assemblyCode) override
    {
        // although push is possible (not like in BoolType, see BoolType.cpp), for consistency with the rest of the code, I do this
        std::shared_ptr<IVariableLocation> stackVar =
            std::shared_ptr<IVariableLocation>(AssemblyCodeGenerator.GetNewLocalVarLocation(this->GetSize(), assemblyCode));
        GenerateAssign(stackVar, source, assemblyCode);
    }

   protected:
    std::string ConstructVarLocationAccess(std::shared_ptr<IVariableLocation> location)
    {
        std::string result = location->ToAssemblyString();

        if (location->RequiresSizeKeyword())
        {
            result = GetSizeKeyword() + " " + result;
        }

        return result;
    }

    void GenerateComparison(std::string comparison, std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                            AssemblyCode* assemblyCode)
    {
        if (destination->RequiresRegister() && source->RequiresRegister())
        {
            source = AssignIVarLocationToRegister(source, assemblyCode);
        }

        AssemblyInstructionLine* line = new AssemblyInstructionLine("cmp");
        line->AddArgument(ConstructVarLocationAccess(destination));
        line->AddArgument(ConstructVarLocationAccess(source));
        assemblyCode->AddLine(line);

        line = new AssemblyInstructionLine("set" + comparison);
        line->AddArgument("al");
        assemblyCode->AddLine(line);

        line = new AssemblyInstructionLine("movzx");
        line->AddArgument(ConstructVarLocationAccess(destination));
        line->AddArgument("al");
        assemblyCode->AddLine(line);
    }

   private:
    void GenerateUsualBinaryOperation(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                                      std::string operation, AssemblyCode* assemblyCode)
    {
        if (destination->RequiresRegister() && source->RequiresRegister())
        {
            source = AssignIVarLocationToRegister(source, assemblyCode);
        }

        AssemblyInstructionLine* line = new AssemblyInstructionLine(operation);
        line->AddArgument(ConstructVarLocationAccess(destination));
        line->AddArgument(ConstructVarLocationAccess(source));
        assemblyCode->AddLine(line);
    }

    /// @brief Generates a binary operation that is applied to the AX register; like mul or div
    void GenerateBinaryOperationOnAXregister(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                                             std::string operation, AssemblyCode* assemblyCode, bool useBX = false)
    {
        if (source->RequiresRegister())
        {
            source = AssignIVarLocationToRegister(source, assemblyCode, useBX);
        }

        if (destination->IsRegister())
        {
            GenerateUsualUnaryOperation(source, operation, assemblyCode);
            return;
        }

        std::shared_ptr<IVariableLocation> axRegister =
            std::shared_ptr<IVariableLocation>(AssemblyCodeGenerator.GetNewAXRegisterVarLocation(this->GetSize(), assemblyCode));

        GenerateAssign(axRegister, destination, assemblyCode);
        GenerateUsualUnaryOperation(source, operation, assemblyCode);
        GenerateAssign(destination, axRegister, assemblyCode);
    }

    void GenerateUsualUnaryOperation(std::shared_ptr<IVariableLocation> destination, std::string operation, AssemblyCode* assemblyCode)
    {
        AssemblyInstructionLine* line = new AssemblyInstructionLine(operation);
        line->AddArgument(ConstructVarLocationAccess(destination));
        assemblyCode->AddLine(line);
    }

    std::string GetSizeKeyword()
    {
        switch (this->GetSize())
        {
            case 1:
                return "byte";
            case 2:
                return "word";
            case 4:
                return "dword";
            case 8:
                return "qword";
        }

        Logger.Log("Cannot get size keyword as argument size is not 1, 2, 4 or 8", Logger::ERROR);
        return "";
    }
};