#pragma once

#include <iostream>

#include "../syntaxTree/SyntaxTree.cpp"
#include "../tokens/TokenList.cpp"
#include "../utils/Logger.cpp"

#pragma region Nodes
#include "../syntaxTree/nodes/line/AbstractLineNode.cpp"

#pragma region Declarations
#include "../syntaxTree/nodes/line/declaration/FuncDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/declaration/GlobalVarDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/declaration/LocalVarDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/declaration/ParameterDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/declaration/PropertyDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/declaration/TypeDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/declaration/VarDeclarationAttributes.cpp"
#include "../syntaxTree/nodes/line/declaration/types/FunctionReturnTypeNode.cpp"

#pragma endregion

#pragma region Expressions
#include "../syntaxTree/nodes/line/expression/AbstractExpressionNode.cpp"
#include "../syntaxTree/nodes/line/expression/AssignmentNode.cpp"
#include "../syntaxTree/nodes/line/expression/BinaryOperatorExpressionNode.cpp"
#include "../syntaxTree/nodes/line/expression/UnaryOperatorExpressionNode.cpp"
#include "../syntaxTree/nodes/line/expression/operators/EAssignOperators.cpp"
#include "../syntaxTree/nodes/line/expression/operators/EOperators.cpp"
#include "../syntaxTree/nodes/line/expression/operators/EUnaryOperators.cpp"
#include "../syntaxTree/nodes/line/expression/values/CallNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/ParenthesisExpressionNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/StructNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/VariableNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/constValues/FloatConstValueNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/constValues/IntConstValueNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/constValues/LogicalConstValueNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/constValues/StringConstValueNode.cpp"

#pragma endregion

#pragma region Statements
#include "../syntaxTree/nodes/line/statement/BodyNode.cpp"
#include "../syntaxTree/nodes/line/statement/EmptyStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/keywordStatement/BreakStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/keywordStatement/ContinueStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/keywordStatement/ElifStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/keywordStatement/ForStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/keywordStatement/IfStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/keywordStatement/ReturnStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/keywordStatement/WhileStatementNode.cpp"

#pragma endregion

#pragma region CompilerInstructions

#include "../syntaxTree/nodes/line/compilerInstruction/ExternInstructionNode.cpp"
#include "../syntaxTree/nodes/line/compilerInstruction/GlobalInstructionNode.cpp"

#pragma endregion

#pragma endregion

static class PredictiveParser
{
   public:
    SyntaxTree* Parse(TokenList* tokens) { return new SyntaxTree(Parse_GlobalCode(tokens)); }

   private:
    /// @brief Consumes and returns next token from TokenList and checks if it is the given expected token. Prints an error message if it is not.
    template <typename T>
    T* ConsumeNext(TokenList* tokens, T& expectedToken)
    {
        static_assert(std::is_base_of<Token, T>::value, "T must be a Token");

        if (!tokens->HasNext())
        {
            Logger.Log("Unexpected end of file expected " + expectedToken.ToString(), Logger::ERROR);
            return nullptr;
        }

        if (!tokens->IsPeekOfTokenType(expectedToken))
        {
            Logger.Log("Unexpected token: " + tokens->Peek()->ToString() + " expected " + expectedToken.ToString(), Logger::ERROR);
            return nullptr;
        }

        return tokens->Next<T>();
    }

    // Explaination for the different Nodes can be found in predictive-parser-table.ods under theoretical_documents in the project root

    bool LookAhead_GlobalCode(TokenList* tokens);
    GlobalCodeNode* Parse_GlobalCode(TokenList* tokens);

    bool LookAhead_BodyCode(TokenList* tokens);
    BodyCodeNode* Parse_BodyCode(TokenList* tokens);

    bool LookAhead_Line(TokenList* tokens);
    AbstractLineNode* Parse_Line(TokenList* tokens);

    bool LookAhead_TypeDefCode(TokenList* tokens);
    TypeDefCodeNode* Parse_TypeDefCode(TokenList* tokens);

// ------- Declarations -------
#pragma region Declarations

    bool LookAhead_Declaration(TokenList* tokens);
    AbstractDeclarationNode* Parse_Declaration(TokenList* tokens);

    bool LookAhead_VarDeclaration(TokenList* tokens);
    /// @param isLocal returns a LocalVarDeclarationNode if true, otherwise a GlobalVarDeclarationNode
    AbstractVarDeclarationNode* Parse_VarDeclaration(TokenList* tokens, bool isLocal);

    bool LookAhead_FuncDeclaration(TokenList* tokens);
    FuncDeclarationNode* Parse_FuncDeclaration(TokenList* tokens);

    bool LookAhead_FunctionReturnType(TokenList* tokens);
    FunctionReturnTypeNode Parse_FunctionReturnType(TokenList* tokens);

    bool LookAhead_VarDeclarationAttributes(TokenList* tokens);
    VarDeclarationAttributes Parse_VarDeclarationAttributes(TokenList* tokens);

    bool LookAhead_TypeDeclaration(TokenList* tokens);
    TypeDeclarationNode* Parse_TypeDeclaration(TokenList* tokens);

    bool LookAhead_PropertyDeclaration(TokenList* tokens);
    PropertyDeclarationNode* Parse_PropertyDeclaration(TokenList* tokens);

    bool LookAhead_Params(TokenList* tokens);
    std::vector<ParameterDeclarationNode*>* Parse_Params(TokenList* tokens);

    bool LookAhead_ParamDeclaration(TokenList* tokens);
    ParameterDeclarationNode* Parse_ParamDeclaration(TokenList* tokens);

    bool LookAhead_Body(TokenList* tokens);
    BodyNode* Parse_Body(TokenList* tokens);

    bool LookAhead_FinalAttribute(TokenList* tokens);
    bool Parse_FinalAttribute(TokenList* tokens);

    bool LookAhead_InlineAttribute(TokenList* tokens);
    bool Parse_InlineAttribute(TokenList* tokens);

#pragma endregion

// ------- Expressions -------
#pragma region Expressions

    bool LookAhead_Expression(TokenList* tokens);
    AbstractExpressionNode* Parse_Expression(TokenList* tokens);

    bool LookAhead_AssignmentExpression(TokenList* tokens);
    AbstractExpressionNode* Parse_AssignmentExpression(TokenList* tokens);

    bool LookAhead_AssignOperator(TokenList* tokens);
    EAssignOperators Parse_AssignOperator(TokenList* tokens);

    bool LookAhead_OrExpression(TokenList* tokens);
    AbstractExpressionNode* Parse_OrExpression(TokenList* tokens);

    bool LookAhead_AndExpression(TokenList* tokens);
    AbstractExpressionNode* Parse_AndExpression(TokenList* tokens);

    bool LookAhead_EqualExpression(TokenList* tokens);
    AbstractExpressionNode* Parse_EqualExpression(TokenList* tokens);

    bool LookAhead_EqualOperator(TokenList* tokens);
    EOperators Parse_EqualOperator(TokenList* tokens);

    bool LookAhead_SumExpression(TokenList* tokens);
    AbstractExpressionNode* Parse_SumExpression(TokenList* tokens);

    bool LookAhead_SumOperator(TokenList* tokens);
    EOperators Parse_SumOperator(TokenList* tokens);

    bool LookAhead_MulExpression(TokenList* tokens);
    AbstractExpressionNode* Parse_MulExpression(TokenList* tokens);

    bool LookAhead_MulOperator(TokenList* tokens);
    EOperators Parse_MulOperator(TokenList* tokens);

    bool LookAhead_UnaryExpression(TokenList* tokens);
    AbstractExpressionNode* Parse_UnaryExpression(TokenList* tokens);

    bool LookAhead_PreUnaryOperator(TokenList* tokens);
    EPreUnaryOperators Parse_PreUnaryOperator(TokenList* tokens);

    bool LookAhead_PostUnaryOperator(TokenList* tokens);
    EPostUnaryOperators Parse_PostUnaryOperator(TokenList* tokens);

    bool LookAhead_Value(TokenList* tokens);
    AbstractValueNode* Parse_Value(TokenList* tokens);

    bool LookAhead_Call(TokenList* tokens);
    CallNode* Parse_Call(TokenList* tokens);

    bool LookAhead_Arguments(TokenList* tokens);
    std::vector<AbstractExpressionNode*> Parse_Arguments(TokenList* tokens);

    bool LookAhead_Parenthesis_Expression(TokenList* tokens);
    ParenthesisExpressionNode* Parse_Parenthesis_Expression(TokenList* tokens);

    bool LookAhead_Struct(TokenList* tokens);
    StructNode* Parse_Struct(TokenList* tokens);

    bool LookAhead_Variable(TokenList* tokens);
    VariableNode* Parse_Variable(TokenList* tokens);

    bool LookAhead_Const(TokenList* tokens);
    AbstractConstValueNode* Parse_Const(TokenList* tokens);

    bool LookAhead_LogicalConst(TokenList* tokens);
    LogicalConstValueNode* Parse_LogicalConst(TokenList* tokens);

#pragma endregion

// ------- Statements -------
#pragma region Statements

    bool LookAhead_Statement(TokenList* tokens);
    AbstractStatementNode* Parse_Statement(TokenList* tokens);

    bool LookAhead_KeywordStatement(TokenList* tokens);
    AbstractKeywordStatementNode* Parse_KeywordStatement(TokenList* tokens);

// ------- Keyword Statements -------
#pragma region KeywordStatements

    bool LookAhead_IfStatement(TokenList* tokens);
    IfStatementNode* Parse_IfStatement(TokenList* tokens);

    bool LookAhead_ElifStatement(TokenList* tokens);
    ElifStatementNode* Parse_ElifStatement(TokenList* tokens);

    bool LookAhead_ElseStatement(TokenList* tokens);
    AbstractStatementNode* Parse_ElseStatement(TokenList* tokens);

    bool LookAhead_ReturnStatement(TokenList* tokens);
    ReturnStatementNode* Parse_ReturnStatement(TokenList* tokens);

    bool LookAhead_WhileStatement(TokenList* tokens);
    WhileStatementNode* Parse_WhileStatement(TokenList* tokens);

    bool LookAhead_ForStatement(TokenList* tokens);
    ForStatementNode* Parse_ForStatement(TokenList* tokens);

    bool LookAhead_BreakStatement(TokenList* tokens);
    BreakStatementNode* Parse_BreakStatement(TokenList* tokens);

    bool LookAhead_ContinueStatement(TokenList* tokens);
    ContinueStatementNode* Parse_ContinueStatement(TokenList* tokens);

#pragma endregion
#pragma endregion

// ------- Compiler Instructions -------
#pragma region CompilerInstructions

    bool LookAhead_CompilerInstruction(TokenList* tokens);
    AbstractCompilerInstructionNode* Parse_CompilerInstruction(TokenList* tokens);

    bool LookAhead_GlobalInstruction(TokenList* tokens);
    GlobalInstructionNode* Parse_GlobalInstruction(TokenList* tokens);

    bool LookAhead_ExternInstruction(TokenList* tokens);
    ExternInstructionNode* Parse_ExternInstruction(TokenList* tokens);

#pragma endregion

} PredictiveParser;