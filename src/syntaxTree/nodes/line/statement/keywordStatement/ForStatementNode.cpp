#pragma once

#include "../../declaration/AbstractVarDeclarationNode.cpp"
#include "../../expression/AbstractExpressionNode.cpp"
#include "AbstractKeywordStatementNode.cpp"

class ForStatementNode : public AbstractKeywordStatementNode
{
   public:
    ForStatementNode(LocalVarDeclarationNode* initialization, AbstractExpressionNode* condition, AbstractStatementNode* increment,
                     AbstractStatementNode* statement)
        : AbstractKeywordStatementNode()
    {
        this->initialization = initialization;
        this->condition = condition;
        this->increment = increment;
        this->statement = statement;
    }

    ~ForStatementNode()
    {
        delete initialization;
        delete condition;
        delete increment;
        delete statement;
    }

    virtual void Traverse(CodeGenerator* codeGenerator, AssemblyCode* assemblyCode) override
    {
        codeGenerator->PushNewEnvironment();
        codeGenerator->SetupLoopJumpLabels();

        this->initialization->Traverse(codeGenerator, assemblyCode);

        std::string startLabel = AssemblyCodeGenerator.GetNewJumpLabel();
        assemblyCode->AddLine(new AssemblyLabelLine(startLabel));

        // Jump to break if condition is false
        this->condition->TraverseConditionalJump(codeGenerator->GetBreakLabel(), true, codeGenerator, assemblyCode);

        this->statement->Traverse(codeGenerator, assemblyCode);
        assemblyCode->AddLine(new AssemblyLabelLine(codeGenerator->GetContinueLabel()));
        this->increment->Traverse(codeGenerator, assemblyCode);
        assemblyCode->AddLine(new AssemblyInstructionLine("jmp " + startLabel));

        assemblyCode->AddLine(new AssemblyLabelLine(codeGenerator->GetBreakLabel()));

        codeGenerator->PopEnvironment(assemblyCode);
    }

    virtual std::string ToString() override
    {
        return "for (" + initialization->ToString() + " " + condition->ToString() + "; " + increment->ToString() + ";)\n" + statement->ToString();
    }

    LocalVarDeclarationNode* initialization;
    AbstractExpressionNode* condition;
    AbstractStatementNode* increment;
    AbstractStatementNode* statement;
};
