#pragma once

#include "../../TypeDefCodeNode.cpp"
#include "AbstractDeclarationNode.cpp"

class TypeDeclarationNode : public AbstractDeclarationNode
{
   public:
    std::string name;
    TypeDefCodeNode* typeDefCode;

    TypeDeclarationNode(std::string name, TypeDefCodeNode* typeDefCode) : AbstractDeclarationNode()
    {
        this->name = name;
        this->typeDefCode = typeDefCode;
    }

    ~TypeDeclarationNode() { delete typeDefCode; }

    virtual void Traverse(CodeGenerator* codeGenerator, AssemblyCode* assemblyCode) override
    {
        if (codeGenerator->DoesTypeExist(this->name))
        {
            Logger.Log("Type " + this->name + " already exists. Cannot be declared again", Logger::ERROR);
            return;
        }

        std::shared_ptr<StructType> structType = this->typeDefCode->TraverseTypeDef(codeGenerator, assemblyCode);
        codeGenerator->AddType(this->name, structType);
    }

    virtual std::string ToString() override { return "typedef " + typeDefCode->ToString() + name + ";"; }
};