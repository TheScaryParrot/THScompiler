#pragma once

#include "../../../../assembly/AssemblyLabelLine.cpp"
#include "../statement/BodyNode.cpp"
#include "AbstractDeclarationNode.cpp"
#include "ParameterDeclarationNode.cpp"
#include "types/FunctionReturnTypeNode.cpp"

class FuncDeclarationNode : public AbstractDeclarationNode
{
   public:
    std::string name;
    FunctionReturnTypeNode returnType;
    std::vector<ParameterDeclarationNode*>* parameters;
    BodyNode* body;

    FuncDeclarationNode(FunctionReturnTypeNode returnType, std::string name, std::vector<ParameterDeclarationNode*>* parameters, BodyNode* body)
        : AbstractDeclarationNode()
    {
        this->returnType = returnType;
        this->name = name;
        this->parameters = parameters;
        this->body = body;
    }

    ~FuncDeclarationNode()
    {
        for (ParameterDeclarationNode* parameter : *parameters)
        {
            delete parameter;
        }

        delete parameters;

        delete body;
    }

    virtual void Traverse(CodeGenerator* codeGenerator, AssemblyCode* assemblyCode) override
    {
        bool isStartFunction = this->name == "_start";

        std::vector<std::shared_ptr<Type>> parameterTypes;

        for (ParameterDeclarationNode* parameter : *this->parameters)
        {
            parameterTypes.push_back(codeGenerator->GetType(parameter->type));
        }

        std::shared_ptr<Type> returnType = nullptr;

        // if not void
        if (!this->returnType.IsVoid())
        {
            returnType = codeGenerator->GetType(this->returnType.name);
        }

        Function* newFunction = new Function(this->name, parameterTypes, returnType);

        codeGenerator->AddFunction(this->name, std::shared_ptr<Function>(newFunction));

        // Generate assembly code
        codeGenerator->PushNewEnvironment();

        for (ParameterDeclarationNode* parameter : *this->parameters)
        {
            parameter->Traverse(codeGenerator, assemblyCode);
        }
        codeGenerator->ClearParameterCounter();

        assemblyCode->AddLine(new AssemblyLabelLine(this->name));

        if (isStartFunction)
        {
            AssemblyCodeGenerator.AddPreStartBody(assemblyCode);
        }
        else
        {
            AssemblyCodeGenerator.AddPreBody(assemblyCode);
        }

        this->body->Traverse(codeGenerator, assemblyCode);

        // Adds exit at the end of start function
        if (isStartFunction)
        {
            AssemblyCodeGenerator.AddPostStartBody(assemblyCode);
        }
        /*
        This part could be added to add ret at the end of EVERY function even if a return is already present
        As this does generate lot of unnecessary rets, it is not added
        else
        {
            AssemblyCodeGenerator.AddPostBody(assemblyCode);
        }

        // Add ret always at the end, not perfect but works
        assemblyCode->AddLine(new AssemblyInstructionLine("ret")); */

        codeGenerator->PopEnvironment(assemblyCode);
    }

    virtual std::string ToString() override
    {
        std::string result = returnType.ToString() + " " + name + "(";

        for (ParameterDeclarationNode* parameter : *parameters)
        {
            result += parameter->ToString() + ", ";
        }

        return result + ")" + body->ToString();
    }
};