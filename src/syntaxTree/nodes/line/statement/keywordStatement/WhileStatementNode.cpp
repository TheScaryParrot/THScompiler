#pragma once

#include <vector>

#include "../../expression/AbstractExpressionNode.cpp"
#include "AbstractKeywordStatementNode.cpp"

class WhileStatementNode : public AbstractKeywordStatementNode
{
   public:
    WhileStatementNode(AbstractExpressionNode* expression, AbstractStatementNode* statement) : AbstractKeywordStatementNode()
    {
        this->expression = expression;
        this->statement = statement;
    }

    ~WhileStatementNode()
    {
        delete expression;
        delete statement;
    }

    virtual void Traverse(CodeGenerator* codeGenerator, AssemblyCode* assemblyCode) override
    {
        codeGenerator->PushNewEnvironment();
        codeGenerator->SetupLoopJumpLabels();

        assemblyCode->AddLine(new AssemblyLabelLine(codeGenerator->GetContinueLabel()));

        // Jump to break if condition is false
        this->expression->TraverseConditionalJump(codeGenerator->GetBreakLabel(), true, codeGenerator, assemblyCode);

        this->statement->Traverse(codeGenerator, assemblyCode);
        assemblyCode->AddLine(new AssemblyInstructionLine("jmp " + codeGenerator->GetContinueLabel()));
        assemblyCode->AddLine(new AssemblyLabelLine(codeGenerator->GetBreakLabel()));

        codeGenerator->PopEnvironment(assemblyCode);
    }

    virtual std::string ToString() override { return "while (" + expression->ToString() + ")\n" + statement->ToString(); }

    AbstractExpressionNode* expression;
    AbstractStatementNode* statement;
};