#pragma once

#include "CharacterGroupToken.cpp"
#include "CompilerInstructionToken.cpp"
#include "KeywordToken.cpp"
#include "TokenWithValue.cpp"
#include "characterGroups/CharacterGroups.cpp"

static class Tokens
{
   public:
    CharacterGroupToken STATEMENT_END_TOKEN = CharacterGroupToken("statementEnd", 0, &CharacterGroups.STATEMENT_END);
    CharacterGroupToken PARENTHESIS_OPEN_TOKEN = CharacterGroupToken("parenthesisOpen", 0, &CharacterGroups.PARENTHESIS_OPEN);
    CharacterGroupToken PARENTHESIS_CLOSE_TOKEN = CharacterGroupToken("parenthesisClose", 0, &CharacterGroups.PARENTHESIS_CLOSE);
    CharacterGroupToken BRACES_OPEN_TOKEN = CharacterGroupToken("bracesOpen", 0, &CharacterGroups.BRACES_OPEN);
    CharacterGroupToken BRACES_CLOSE_TOKEN = CharacterGroupToken("bracesClose", 0, &CharacterGroups.BRACES_CLOSE);
    CharacterGroupToken SEPERATOR_TOKEN = CharacterGroupToken("seperator", 0, &CharacterGroups.SEPERATOR);

    CharacterGroupToken EQUAL_OPERATOR_TOKEN = CharacterGroupToken("equalOperator", 0, &CharacterGroups.EQUAL_OPERATOR);
    CharacterGroupToken NOT_EQUAL_OPERATOR_TOKEN = CharacterGroupToken("notEqualOperator", 0, &CharacterGroups.NOT_EQUAL_OPERATOR);
    CharacterGroupToken LESS_THAN_OPERATOR_TOKEN = CharacterGroupToken("lessThanOperator", 0, &CharacterGroups.LESS_THAN_OPERATOR);
    CharacterGroupToken GREATER_THAN_OPERATOR_TOKEN = CharacterGroupToken("greaterThanOperator", 0, &CharacterGroups.GREATER_THAN_OPERATOR);
    CharacterGroupToken LESS_THAN_OR_EQUAL_OPERATOR_TOKEN =
        CharacterGroupToken("lessOrEqualOperator", 0, &CharacterGroups.LESS_THAN_OR_EQUAL_OPERATOR);
    CharacterGroupToken GREATER_THAN_OR_EQUAL_OPERATOR_TOKEN =
        CharacterGroupToken("greaterOrEqualOperator", 0, &CharacterGroups.GREATER_THAN_OR_EQUAL_OPERATOR);

    CharacterGroupToken ADD_OPERATOR_TOKEN = CharacterGroupToken("addOperator", 0, &CharacterGroups.ADD_OPERATOR);
    CharacterGroupToken SUB_OPERATOR_TOKEN = CharacterGroupToken("subOperator", 0, &CharacterGroups.SUB_OPERATOR);
    CharacterGroupToken MUL_OPERATOR_TOKEN = CharacterGroupToken("mulOperator", 0, &CharacterGroups.MUL_OPERATOR);
    CharacterGroupToken DIV_OPERATOR_TOKEN = CharacterGroupToken("divOperator", 0, &CharacterGroups.DIV_OPERATOR);
    CharacterGroupToken MOD_OPERATOR_TOKEN = CharacterGroupToken("modOperator", 0, &CharacterGroups.MOD_OPERATOR);

    CharacterGroupToken ASSIGN_OPERATOR_TOKEN = CharacterGroupToken("assignOperator", 0, &CharacterGroups.ASSIGN_OPERATOR);
    CharacterGroupToken ADD_ASSIGN_OPERATOR_TOKEN = CharacterGroupToken("addAssignOperator", 0, &CharacterGroups.ADD_ASSIGN_OPERATOR);
    CharacterGroupToken SUB_ASSIGN_OPERATOR_TOKEN = CharacterGroupToken("subAssignOperator", 0, &CharacterGroups.SUB_ASSIGN_OPERATOR);
    CharacterGroupToken MUL_ASSIGN_OPERATOR_TOKEN = CharacterGroupToken("mulAssignOperator", 0, &CharacterGroups.MUL_ASSIGN_OPERATOR);
    CharacterGroupToken DIV_ASSIGN_OPERATOR_TOKEN = CharacterGroupToken("divAssignOperator", 0, &CharacterGroups.DIV_ASSIGN_OPERATOR);
    CharacterGroupToken MOD_ASSIGN_OPERATOR_TOKEN = CharacterGroupToken("modAssignOperator", 0, &CharacterGroups.MOD_ASSIGN_OPERATOR);

    CharacterGroupToken INCREMENT_OPERATOR_TOKEN = CharacterGroupToken("incrementOperator", 0, &CharacterGroups.INCREMENT_OPERATOR);
    CharacterGroupToken DECREMENT_OPERATOR_TOKEN = CharacterGroupToken("decrementOperator", 0, &CharacterGroups.DECREMENT_OPERATOR);

    CharacterGroupToken NEGATE_OPERATOR_TOKEN = CharacterGroupToken("negateOperator", 0, &CharacterGroups.NEGATE_OPERATOR);

    CharacterGroupToken NOT_OPERATOR_TOKEN = CharacterGroupToken("notOperator", 0, &CharacterGroups.NOT_OPERATOR);
    CharacterGroupToken AND_OPERATOR_TOKEN = CharacterGroupToken("andOperator", 0, &CharacterGroups.AND_OPERATOR);
    CharacterGroupToken OR_OPERATOR_TOKEN = CharacterGroupToken("orOperator", 0, &CharacterGroups.OR_OPERATOR);

    CharacterGroupToken DOT_TOKEN = CharacterGroupToken("dot", 0, &CharacterGroups.DOT);

    /* Tokens with Value */
    TokenWithValue CONST_IDENTIFIER_TOKEN = TokenWithValue("idToken", 0, "");
    TokenWithValue CONST_INT_TOKEN = TokenWithValue("intToken", 0, "0");
    TokenWithValue CONST_FLOAT_TOKEN = TokenWithValue("floatToken", 0, "0.0");
    TokenWithValue CONST_STRING_TOKEN = TokenWithValue("stringToken", 0, "");

    /* Keyword Tokens */
    KeywordToken IF_KEYWORD = KeywordToken("if", 0);
    KeywordToken ELSE_KEYWORD = KeywordToken("else", 0);
    KeywordToken ELIF_KEYWORD = KeywordToken("elif", 0);

    KeywordToken WHILE_KEYWORD = KeywordToken("while", 0);
    KeywordToken FOR_KEYWORD = KeywordToken("for", 0);
    KeywordToken BREAK_KEYWORD = KeywordToken("break", 0);
    KeywordToken CONTINUE_KEYWORD = KeywordToken("continue", 0);

    KeywordToken LOGICAL_TRUE_KEYWORD = KeywordToken("true", 0);
    KeywordToken LOGICAL_FALSE_KEYWORD = KeywordToken("false", 0);

    KeywordToken RETURN_KEYWORD = KeywordToken("return", 0);
    KeywordToken VOID_KEYWORD = KeywordToken("void", 0);

    KeywordToken FINAL_KEYWORD = KeywordToken("final", 0);
    KeywordToken INLINE_KEYWORD = KeywordToken("inline", 0);

    KeywordToken TYPEDEF_KEYWORD = KeywordToken("typedef", 0);

    /* Compiler Instructions */
    CompilerInstructionToken EXTERN_INSTRUCTION = CompilerInstructionToken("extern", 0);
    CompilerInstructionToken GLOBAL_INSTRUCTION = CompilerInstructionToken("global", 0);

} Tokens;