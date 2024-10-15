#pragma once

#include <memory>
#include <vector>

#include "line/AbstractLineNode.cpp"

class BodyCodeNode : AbstractTreeNode
{
   public:
    void AddLine(AbstractLineNode* line);
    AbstractLineNode* GetLine(int index);
    unsigned int GetLineCount();

    virtual void Traverse(CodeGenerator* codeGenerator, AssemblyCode* assemblyCode) override
    {
        for (unsigned int i = 0; i < this->GetLineCount(); i++)
        {
            AbstractLineNode* lineNode = this->GetLine(i);

            if (lineNode == nullptr) continue;

            lineNode->Traverse(codeGenerator, assemblyCode);
        }
    }

    std::string ToString();

   private:
    std::vector<std::unique_ptr<AbstractLineNode>> lines;
};

void BodyCodeNode::AddLine(AbstractLineNode* codeLine) { lines.push_back(std::unique_ptr<AbstractLineNode>(codeLine)); }

AbstractLineNode* BodyCodeNode::GetLine(int index) { return lines[index].get(); }

unsigned int BodyCodeNode::GetLineCount() { return lines.size(); }

std::string BodyCodeNode::ToString()
{
    std::string result = "{\n";

    for (std::unique_ptr<AbstractLineNode>& line : lines)
    {
        result += "\t" + line->ToString() + "\n";
    }

    result += "}";

    return result;
}