#pragma once

#include "../../../../codeGenerator/types/StructType.cpp"
#include "AbstractDeclarationNode.cpp"
#include "types/TypeNode.cpp"

class PropertyDeclarationNode : public AbstractDeclarationNode
{
   public:
    PropertyDeclarationNode(TypeNode type, std::string name)
    {
        this->type = type;
        this->name = name;
    }

    void TraversePropertyDeclaration(StructType* structType, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
    {
        std::shared_ptr<Type> type = codeGenerator->GetType(this->type.name);
        structType->AddProperty(this->name, type);
    }

    virtual void Traverse(CodeGenerator* codeGenerator, AssemblyCode* assemblyCode) override
    {
        Logger.Log(
            "PropertyDeclarationNode::Traverse() is not suppost to be called, use TraversePropertyDeclaration() instead as it requires a additional "
            "argument",
            Logger::ERROR);
    }

    virtual std::string ToString() override { return "property " + type.ToString() + " " + name + ";"; };

    std::string name;
    TypeNode type;

   private:
    StructType* traverseArg1;
};