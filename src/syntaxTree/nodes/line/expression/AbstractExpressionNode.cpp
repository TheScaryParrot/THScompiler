#pragma once

#include "../statement/AbstractStatementNode.cpp"

/// @brief Node used for everything that is an expression. So also sumExp or unaryExp
class AbstractExpressionNode : public AbstractStatementNode
{
   public:
    virtual bool RequiresAXRegister() = 0;

    virtual std::shared_ptr<Variable> TraverseExpression(CodeGenerator* codeGenerator, AssemblyCode* assemblyCode) = 0;

    /// @brief Generates a conditional jump based on the expression
    /// @param label Where to jump
    /// @param inverseCondition If true, jumps if the expression is false. Normally jumps if the expression is true
    virtual void TraverseConditionalJump(std::string label, bool inverseCondition, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
    {
        // Standard implementation: Jump if not false

        std::shared_ptr<Variable> condition = TraverseExpression(codeGenerator, assemblyCode);

        // Generate constant false variable
        std::shared_ptr<BoolConstVarLocation> falseLocation = std::shared_ptr<BoolConstVarLocation>(new BoolConstVarLocation(false));
        std::shared_ptr<Variable> falseVariable = std::shared_ptr<Variable>(new Variable(falseLocation, codeGenerator->GetType("bool"), true));

        codeGenerator->GenerateConditionalJump(condition, falseVariable, inverseCondition, EOperators::NOT_EQUAL_OPERATOR, label, assemblyCode);
    }

    virtual void Traverse(CodeGenerator* codeGenerator, AssemblyCode* assemblyCode) override { TraverseExpression(codeGenerator, assemblyCode); }
};