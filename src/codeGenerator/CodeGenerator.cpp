#pragma once

#include <string>

#include "../assembly/AssemblyCodeGenerator.cpp"
#include "../syntaxTree/nodes/line/expression/operators/EOperators.cpp"
#include "Variable.cpp"
#include "environment/EnvironmentLinkedList.cpp"
#include "types/Type.cpp"
#include "types/primitiveTypes/BoolType.cpp"
#include "types/primitiveTypes/CharType.cpp"
#include "types/primitiveTypes/FloatType.cpp"
#include "types/primitiveTypes/IntType.cpp"
#include "varLocation/RegistryPointerVarLocation.cpp"
#include "varLocation/constVarLocations/BoolConstVarLocation.cpp"
#include "varLocation/constVarLocations/FloatConstVarLocation.cpp"
#include "varLocation/constVarLocations/IntConstVarLocation.cpp"

/// @brief Class containing many helper functions for code generation, is accessed by the AST nodes using a visitor pattern
class CodeGenerator
{
   private:
    EnvironmentLinkedList environmentLinkedList;

    void AddPrimitiveTypes()
    {
        AddType("int", std::shared_ptr<Type>(new IntType()));
        AddType("float", std::shared_ptr<Type>(new FloatType()));
        AddType("char", std::shared_ptr<Type>(new CharType()));
        AddType("bool", std::shared_ptr<Type>(new BoolType()));
    }

   public:
    CodeGenerator()
    {
        this->environmentLinkedList = EnvironmentLinkedList();
        environmentLinkedList.PushEnvironment(new Environment(0));
        AssemblyCodeGenerator.SetLocalVariableOffset(environmentLinkedList.GetLocalVariableOffset());
        AddPrimitiveTypes();
    }

    bool DoesVariableExist(std::string variableName) { return environmentLinkedList.DoesVariableExist(variableName); }
    std::shared_ptr<Variable> GetVariable(std::string variableName) { return environmentLinkedList.GetVariable(variableName); }
    void AddVariable(std::string variableName, std::shared_ptr<Variable> variable) { environmentLinkedList.AddVariable(variableName, variable); }

    bool DoesFunctionExist(std::string functionName) { return environmentLinkedList.DoesFunctionExist(functionName); }
    std::shared_ptr<Function> GetFunction(std::string functionName) { return environmentLinkedList.GetFunction(functionName); }
    void AddFunction(std::string functionName, std::shared_ptr<Function> function) { environmentLinkedList.AddFunction(functionName, function); }

    bool DoesTypeExist(std::string typeName) { return environmentLinkedList.DoesTypeExist(typeName); }
    std::shared_ptr<Type> GetType(std::string typeName) { return environmentLinkedList.GetType(typeName); }
    void AddType(std::string typeName, std::shared_ptr<Type> type) { environmentLinkedList.AddType(typeName, type); }

    Variable* GetAXRegisterVariable(std::shared_ptr<Type> type, bool isFinal, AssemblyCode* assemblyCode)
    {
        IVariableLocation* location = AssemblyCodeGenerator.GetNewAXRegisterVarLocation(type->GetSize(), assemblyCode);
        return new Variable(std::shared_ptr<IVariableLocation>(location), type, isFinal);
    }
    Variable* GetNewLocalVariable(std::shared_ptr<Type> type, bool isFinal, AssemblyCode* assemblyCode)
    {
        IVariableLocation* location = AssemblyCodeGenerator.GetNewLocalVarLocation(type->GetSize(), assemblyCode);
        return new Variable(std::shared_ptr<IVariableLocation>(location), type, isFinal);
    }

    Variable* GetNewParameterVariable(std::shared_ptr<Type> type, bool isFinal, AssemblyCode* assemblyCode)
    {
        IVariableLocation* location = AssemblyCodeGenerator.GetNewParameterLocation(type->GetSize(), assemblyCode);
        return new Variable(std::shared_ptr<IVariableLocation>(location), type, isFinal);
    }
    void ClearParameterCounter() { AssemblyCodeGenerator.ClearParameterCounter(); }

    IConstVarLocation* PerformConstantBinaryOperatorOnVariables(IConstVarLocation* left, IConstVarLocation* right, EOperators op)
    {
        switch (op)
        {
            case EOperators::ADD_OPERATOR:
                return left->GenerateAdd(right);
            case EOperators::SUB_OPERATOR:
                return left->GenerateSub(right);
            case EOperators::MUL_OPERATOR:
                return left->GenerateMul(right);
            case EOperators::DIV_OPERATOR:
                return left->GenerateDiv(right);
            case EOperators::MOD_OPERATOR:
                return left->GenerateMod(right);
            case EOperators::AND_OPERATOR:
                return left->GenerateAnd(right);
            case EOperators::OR_OPERATOR:
                return left->GenerateOr(right);
            case EOperators::EQUAL_OPERATOR:
                return left->GenerateEqual(right);
            case EOperators::NOT_EQUAL_OPERATOR:
                return left->GenerateNotEqual(right);
            case EOperators::LESS_THAN_OPERATOR:
                return left->GenerateLess(right);
            case EOperators::LESS_THAN_OR_EQUAL_OPERATOR:
                return left->GenerateLessEqual(right);
            case EOperators::GREATER_THAN_OPERATOR:
                return left->GenerateGreater(right);
                break;
            case EOperators::GREATER_THAN_OR_EQUAL_OPERATOR:
                return left->GenerateGreaterEqual(right);
            default:
                Logger.Log("Unknown operator for constant binary operation", Logger::ERROR);
                return nullptr;
        }
    }

    /// @brief Applies operator on two variables. If both variables are inline then the result is also inline. If only left is inline a new
    /// localVariable will be created and returned.
    /// @return Where the result is stored
    std::shared_ptr<Variable> ApplyBinaryOperatorOnVariables(std::shared_ptr<Variable> left, std::shared_ptr<Variable> right, EOperators op,
                                                             AssemblyCode* assemblyCode)
    {
        if (left == nullptr)
        {
            Logger.Log("Left variable in binaryOperatorExpression is null", Logger::ERROR);
            return nullptr;
        }

        if (right == nullptr)
        {
            Logger.Log("Right variable in binaryOperatorExpression is null", Logger::ERROR);
            return nullptr;
        }

        if (!left->type->CanApplyToThis(right->type.get()))
        {
            Logger.Log("Cannot apply operation in binaryOperatorExpression", Logger::ERROR);
            return nullptr;
        }

        std::shared_ptr<IVariableLocation> leftLocation = left->location;
        std::shared_ptr<IVariableLocation> rightLocation = right->location;

        if (left->IsInline())
        {
            if (right->IsInline())
            {
                IConstVarLocation* leftConstLocation = dynamic_cast<IConstVarLocation*>(leftLocation.get());
                if (leftConstLocation == nullptr)
                {
                    Logger.Log("Left variable " + rightLocation->ToAssemblyString() + " is marked as inline but it's variable location is not const",
                               Logger::ERROR);
                    return nullptr;
                }

                IConstVarLocation* rightConstLocation = dynamic_cast<IConstVarLocation*>(rightLocation.get());
                if (rightConstLocation == nullptr)
                {
                    Logger.Log("Right variable " + rightLocation->ToAssemblyString() + " is marked as inline but it's variable location is not const",
                               Logger::ERROR);
                    return nullptr;
                }

                IConstVarLocation* result = PerformConstantBinaryOperatorOnVariables(leftConstLocation, rightConstLocation, op);
                return std::shared_ptr<Variable>(new Variable(std::shared_ptr<IVariableLocation>(result), left->type, true));
            }
            else
            {
                // If the right location is AX safe it in DX and left in AX. This ensures 1. AX is not overriden, 2. that always AX and never DX is
                // returned as the result
                if (right->location->IsRegister())
                {
                    std::shared_ptr<IVariableLocation> dxRegister =
                        std::shared_ptr<IVariableLocation>(AssemblyCodeGenerator.GetNewDXRegisterVarLocation(right->type->GetSize(), assemblyCode));
                    right->type->GenerateAssign(dxRegister, right->location, assemblyCode);
                    rightLocation = dxRegister;
                }

                Variable* axRegister = GetAXRegisterVariable(left->type, false, assemblyCode);
                left->type->GenerateAssign(axRegister->location, leftLocation, assemblyCode);
                left = std::shared_ptr<Variable>(axRegister);
                leftLocation = left->location;
            }
        }

        switch (op)
        {
            case EOperators::ASSIGN_OPERATOR:
                left->type->GenerateAssign(leftLocation, rightLocation, assemblyCode);
                break;
            case EOperators::ADD_OPERATOR:
                left->type->GenerateAdd(leftLocation, rightLocation, assemblyCode);
                break;
            case EOperators::SUB_OPERATOR:
                left->type->GenerateSub(leftLocation, rightLocation, assemblyCode);
                break;
            case EOperators::MUL_OPERATOR:
                left->type->GenerateMul(leftLocation, rightLocation, assemblyCode);
                break;
            case EOperators::DIV_OPERATOR:
                left->type->GenerateDiv(leftLocation, rightLocation, assemblyCode);
                break;
            case EOperators::MOD_OPERATOR:
                left->type->GenerateMod(leftLocation, rightLocation, assemblyCode);
                break;
            case EOperators::AND_OPERATOR:
                left->type->GenerateAnd(leftLocation, rightLocation, assemblyCode);
                break;
            case EOperators::OR_OPERATOR:
                left->type->GenerateOr(leftLocation, rightLocation, assemblyCode);
                break;
            case ::EOperators::EQUAL_OPERATOR:
                left->type->GenerateEqual(leftLocation, rightLocation, assemblyCode);
                break;
            case EOperators::NOT_EQUAL_OPERATOR:
                left->type->GenerateNotEqual(leftLocation, rightLocation, assemblyCode);
                break;
            case EOperators::LESS_THAN_OPERATOR:
                left->type->GenerateLess(leftLocation, rightLocation, assemblyCode);
                break;
            case EOperators::LESS_THAN_OR_EQUAL_OPERATOR:
                left->type->GenerateLessEqual(leftLocation, rightLocation, assemblyCode);
                break;
            case EOperators::GREATER_THAN_OPERATOR:
                left->type->GenerateGreater(leftLocation, rightLocation, assemblyCode);
                break;
            case EOperators::GREATER_THAN_OR_EQUAL_OPERATOR:
                left->type->GenerateGreaterEqual(leftLocation, rightLocation, assemblyCode);
                break;
        }

        return left;
    }

    void PushNewEnvironment()
    {
        environmentLinkedList.PushEnvironment(new Environment(*environmentLinkedList.GetLocalVariableOffset()));
        AssemblyCodeGenerator.SetLocalVariableOffset(environmentLinkedList.GetLocalVariableOffset());  // Update reference to local variable offset
    }
    void PopEnvironment(AssemblyCode* assemblyCode)
    {
        unsigned int oldOffset = *environmentLinkedList.GetLocalVariableOffset();
        environmentLinkedList.PopEnvironment();
        unsigned int* newOffset = environmentLinkedList.GetLocalVariableOffset();
        AssemblyCodeGenerator.SetLocalVariableOffset(newOffset);  // Update reference to local variable offset

        if (oldOffset != *newOffset)
        {
            // forget about the variables that are no longer in scope
            AssemblyCodeGenerator.IncrementRSP(oldOffset - *newOffset, assemblyCode);
        }
    }

    std::string GetBreakLabel() { return environmentLinkedList.GetJumpLabel("break"); }
    std::string GetContinueLabel() { return environmentLinkedList.GetJumpLabel("continue"); }
    void SetupLoopJumpLabels()
    {
        environmentLinkedList.AddJumpLabel("break", AssemblyCodeGenerator.GetNewJumpLabel());
        environmentLinkedList.AddJumpLabel("continue", AssemblyCodeGenerator.GetNewJumpLabel());
    }

    bool IsConditionalOperator(EOperators op)
    {
        switch (op)
        {
            case EOperators::EQUAL_OPERATOR:
            case EOperators::NOT_EQUAL_OPERATOR:
            case EOperators::LESS_THAN_OPERATOR:
            case EOperators::LESS_THAN_OR_EQUAL_OPERATOR:
            case EOperators::GREATER_THAN_OPERATOR:
            case EOperators::GREATER_THAN_OR_EQUAL_OPERATOR:
                return true;
            default:
                return false;
        }
    }
    std::string GetConditionalJump(EOperators conditionalOperator)
    {
        switch (conditionalOperator)
        {
            case EOperators::EQUAL_OPERATOR:
                return "je";
            case EOperators::NOT_EQUAL_OPERATOR:
                return "jne";
            case EOperators::LESS_THAN_OPERATOR:
                return "jl";
            case EOperators::LESS_THAN_OR_EQUAL_OPERATOR:
                return "jle";
            case EOperators::GREATER_THAN_OPERATOR:
                return "jg";
            case EOperators::GREATER_THAN_OR_EQUAL_OPERATOR:
                return "jge";
            default:
                Logger.Log("Unknown operator for conditional jump", Logger::ERROR);
                return "";
        }
    }
    EOperators InverseConditionalOperator(EOperators conditionalOperator)
    {
        switch (conditionalOperator)
        {
            case EOperators::EQUAL_OPERATOR:
                return EOperators::NOT_EQUAL_OPERATOR;
            case EOperators::NOT_EQUAL_OPERATOR:
                return EOperators::EQUAL_OPERATOR;
            case EOperators::LESS_THAN_OPERATOR:
                return EOperators::GREATER_THAN_OR_EQUAL_OPERATOR;
            case EOperators::LESS_THAN_OR_EQUAL_OPERATOR:
                return EOperators::GREATER_THAN_OPERATOR;
            case EOperators::GREATER_THAN_OPERATOR:
                return EOperators::LESS_THAN_OR_EQUAL_OPERATOR;
            case EOperators::GREATER_THAN_OR_EQUAL_OPERATOR:
                return EOperators::LESS_THAN_OPERATOR;
            default:
                Logger.Log("Unknown operator for conditional jump", Logger::ERROR);
                return EOperators::EQUAL_OPERATOR;
        }
    }

    /// @brief Generates a comparison and jump to label if the comparison is true
    /// @param conditionalOperator Condition to check. Must be a comparison operator
    /// @param label Label to jump to if the condition is true
    /// @param inverseCondition If true the conditionalOperator is inverted
    void GenerateConditionalJump(std::shared_ptr<Variable> left, std::shared_ptr<Variable> right, bool inverseCondition,
                                 EOperators conditionalOperator, std::string label, AssemblyCode* assemblyCode)
    {
        if (left == nullptr)
        {
            Logger.Log("Left Variable in GenerateConditionalJump is null", Logger::ERROR);
            return;
        }

        if (right == nullptr)
        {
            Logger.Log("Right Variable in GenerateConditionalJump is null", Logger::ERROR);
            return;
        }

        if (!left->type->CanApplyToThis(right->type.get()))
        {
            Logger.Log("Condition " + left.get()->ToString() + " must be of type bool for conditional jump", Logger::ERROR);
            return;
        }

        std::shared_ptr<IVariableLocation> leftLocation = left->location;
        std::shared_ptr<IVariableLocation> rightLocation = right->location;

        if (inverseCondition) conditionalOperator = InverseConditionalOperator(conditionalOperator);

        if (left->IsInline() && right->IsInline())
        {
            // Calculate the result of the comparison
            IConstVarLocation* result = PerformConstantBinaryOperatorOnVariables(
                dynamic_cast<IConstVarLocation*>(leftLocation.get()), dynamic_cast<IConstVarLocation*>(rightLocation.get()), conditionalOperator);

            // Jump if the result is not zero (true)
            if (!result->IsZero())
            {
                assemblyCode->AddLine(new AssemblyInstructionLine("jmp " + label));
            }

            delete result;
            return;
        }

        std::string jump = GetConditionalJump(conditionalOperator);

        if (jump == "")
        {
            Logger.Log("Unknown operator for conditional jump", Logger::ERROR);
            return;
        }

        // If a register is required, save the left variable in DX
        bool requiresRegister = leftLocation->RequiresRegister() && rightLocation->RequiresRegister();
        if (requiresRegister)
        {
            // Overwrite the left variable
            leftLocation = std::shared_ptr<IVariableLocation>(AssemblyCodeGenerator.GetNewDXRegisterVarLocation(left->type->GetSize(), assemblyCode));
            left->type->GenerateAssign(leftLocation, left->location, assemblyCode);
        }

        // Compare the two variables
        AssemblyInstructionLine* cmpLine = new AssemblyInstructionLine("cmp");
        cmpLine->AddArgument(leftLocation->ToAssemblyString());
        cmpLine->AddArgument(rightLocation->ToAssemblyString());
        assemblyCode->AddLine(cmpLine);

        // jump if condition is true
        assemblyCode->AddLine(new AssemblyInstructionLine(jump + " " + label));
    }
};