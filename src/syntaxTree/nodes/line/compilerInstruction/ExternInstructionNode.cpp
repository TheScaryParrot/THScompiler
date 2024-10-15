#pragma once

#include <vector>

#include "../declaration/ParameterDeclarationNode.cpp"
#include "../declaration/types/FunctionReturnTypeNode.cpp"
#include "AbstractCompilerInstructionNode.cpp"

class ExternInstructionNode : public AbstractCompilerInstructionNode
{
   public:
    FunctionReturnTypeNode returnType;
    std::string identifier;
    std::vector<ParameterDeclarationNode*>* parameters;

    ExternInstructionNode(FunctionReturnTypeNode returnType, std::string identifier, std::vector<ParameterDeclarationNode*>* parameters)
        : AbstractCompilerInstructionNode()
    {
        this->returnType = returnType;
        this->identifier = identifier;
        this->parameters = parameters;
    }

    ~ExternInstructionNode()
    {
        for (ParameterDeclarationNode* parameter : *parameters)
        {
            delete parameter;
        }

        delete parameters;
    }

    virtual void Traverse(CodeGenerator* codeGenerator, AssemblyCode* assemblyCode) override
    {
        // extern keyword just adds the function to environment
        // and writes extern IDENTIFIER in assembly code
        // implementation is added in linking phase

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

        Function* newFunction = new Function(this->identifier, parameterTypes, returnType);

        codeGenerator->AddFunction(this->identifier, std::shared_ptr<Function>(newFunction));

        AssemblyInstructionLine* externLine = new AssemblyInstructionLine("extern");
        externLine->AddArgument(this->identifier);
        assemblyCode->AddLine(externLine);
    }

    virtual std::string ToString() override
    {
        std::string result = "extern " + returnType.ToString() + " " + identifier + "(";

        for (ParameterDeclarationNode* parameter : *parameters)
        {
            result += parameter->ToString() + ", ";
        }

        return result + ");";
    }
};