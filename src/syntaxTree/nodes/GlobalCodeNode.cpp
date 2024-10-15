#pragma once

#include <memory>
#include <vector>

#include "line/AbstractLineNode.cpp"

class GlobalCodeNode : AbstractTreeNode
{
   public:
    void AddLineNode(AbstractLineNode* line) { lines.push_back(std::unique_ptr<AbstractLineNode>(line)); }
    AbstractLineNode* GetLine(int index) { return lines[index].get(); }
    unsigned int GetLineCount() { return lines.size(); }

    virtual void Traverse(CodeGenerator* codeGenerator, AssemblyCode* assemblyCode) override
    {
        for (unsigned int i = 0; i < this->GetLineCount(); i++)
        {
            AbstractLineNode* line = this->GetLine(i);

            if (line == nullptr) continue;

            line->Traverse(codeGenerator, assemblyCode);
        }
    }

    std::string ToString()
    {
        std::string result = "{\n";

        for (std::unique_ptr<AbstractLineNode>& line : lines)
        {
            result += "\t" + line->ToString() + "\n";
        }

        result += "}";

        return result;
    }

   private:
    std::vector<std::unique_ptr<AbstractLineNode>> lines;
};