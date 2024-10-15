#pragma once

#include <memory>
#include <vector>

#include "line/declaration/PropertyDeclarationNode.cpp"

class TypeDefCodeNode : AbstractTreeNode
{
   public:
    ~TypeDefCodeNode()
    {
        for (auto& line : lines)
        {
            delete line;
        }
    }

    void AddProperty(PropertyDeclarationNode* line) { lines.push_back(line); }
    PropertyDeclarationNode* GetProperty(int index) { return lines[index]; }
    unsigned int GetLineCount() { return lines.size(); }

    std::shared_ptr<StructType> TraverseTypeDef(CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
    {
        StructType* structType = new StructType();

        for (unsigned int i = 0; i < this->GetLineCount(); i++)
        {
            PropertyDeclarationNode* declaration = this->GetProperty(i);

            if (declaration == nullptr) continue;

            declaration->TraversePropertyDeclaration(structType, codeGenerator, assemblyCode);
        }

        return std::shared_ptr<StructType>(structType);
    }

    virtual void Traverse(CodeGenerator* codeGenerator, AssemblyCode* assemblyCode) override { TraverseTypeDef(codeGenerator, assemblyCode); }

    std::string ToString()
    {
        std::string result = "{\n";

        for (auto& line : lines)
        {
            result += "\t" + line->ToString() + "\n";
        }

        result += "}";

        return result;
    }

   private:
    std::vector<PropertyDeclarationNode*> lines;
};