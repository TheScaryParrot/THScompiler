#pragma once

#include "../../BodyCodeNode.cpp"
#include "../statement/AbstractStatementNode.cpp"

class BodyNode : public AbstractStatementNode
{
   public:
    BodyNode() : AbstractStatementNode() { this->bodyCodeNode = new BodyCodeNode(); }
    BodyNode(BodyCodeNode* BodyCodeNode) : AbstractStatementNode() { this->bodyCodeNode = bodyCodeNode; }
    ~BodyNode() { delete bodyCodeNode; }

    void AddCodeLine(AbstractLineNode* codeLine) { bodyCodeNode->AddLine(codeLine); }

    BodyCodeNode* GetCodeBlock() { return bodyCodeNode; }

    virtual void Traverse(CodeGenerator* codeGenerator, AssemblyCode* assemblyCode) override
    {
        codeGenerator->PushNewEnvironment();
        this->GetCodeBlock()->Traverse(codeGenerator, assemblyCode);
        codeGenerator->PopEnvironment(assemblyCode);
    }

    virtual std::string ToString() override { return bodyCodeNode->ToString(); }

   private:
    BodyCodeNode* bodyCodeNode;
};