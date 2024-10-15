#pragma once

#include <string>
#include <vector>

#include "AbstractValueNode.cpp"

class CallNode : public AbstractValueNode
{
   public:
    CallNode(std::string functionName, std::vector<AbstractExpressionNode*> arguments)
    {
        this->functionName = functionName;
        this->arguments = arguments;
    }

    ~CallNode()
    {
        for (AbstractExpressionNode* argument : arguments)
        {
            delete argument;
        }
    }

    virtual bool RequiresAXRegister() override { return true; }

    virtual std::shared_ptr<Variable> TraverseExpression(CodeGenerator* codeGenerator, AssemblyCode* assemblyCode) override
    {
        // Create new environment for arguments
        codeGenerator->PushNewEnvironment();

        std::shared_ptr<Function> function = codeGenerator->GetFunction(this->functionName);

        if (function == nullptr)
        {
            Logger.Log("Function " + this->functionName + " does not exist", Logger::ERROR);
            return nullptr;
        }

        std::vector<std::shared_ptr<Variable>> arguments;

        for (AbstractExpressionNode* argument : this->arguments)
        {
            std::shared_ptr<Variable> argumentVariable = argument->TraverseExpression(codeGenerator, assemblyCode);
            arguments.push_back(argumentVariable);
        }

        // If wrong argument type
        for (size_t i = 0; i < arguments.size(); i++)
        {
            if (!function->parameterTypes[i]->CanApplyToThis(arguments[i]->type.get()))
            {
                Logger.Log("Argument " + std::to_string(i) + " of function " + this->functionName + " has wrong type", Logger::ERROR);
                return nullptr;
            }
        }

        // Push arguments to stack in reverse order
        for (int i = arguments.size() - 1; i >= 0; i--)
        {
            arguments[i]->type->GenerateStackPush(arguments[i]->location, assemblyCode);
        }

        AssemblyCodeGenerator.AddPreCall(assemblyCode);
        function->GenerateCallInstruction(assemblyCode);
        AssemblyCodeGenerator.AddPostCall(assemblyCode);

        // Pop argument environment
        codeGenerator->PopEnvironment(assemblyCode);

        // if void
        if (function->returnType == nullptr)
        {
            return nullptr;
        }

        // return is stored on stack at location pointed at by rax
        std::shared_ptr<IVariableLocation> returnVariable = std::shared_ptr<IVariableLocation>(new RegistryPointerVarLocation("rax", 0));
        Variable* localVariable = codeGenerator->GetNewLocalVariable(function->returnType, false, assemblyCode);

        // Assign return value to local variable
        localVariable->type->GenerateAssign(localVariable->location, returnVariable, assemblyCode);

        return std::shared_ptr<Variable>(localVariable);
    }

    virtual std::string ToString() override
    {
        std::string result = functionName + "(";

        for (AbstractExpressionNode* argument : arguments)
        {
            result += argument->ToString() + ", ";
        }

        return result + ")";
    }

    std::string functionName;
    std::vector<AbstractExpressionNode*> arguments;
};
