#pragma once

#include "../../tokens/Tokens.cpp"
#include "../PredictiveParser.hpp"

bool PredictiveParser::LookAhead_Declaration(TokenList* tokens)
{
    return LookAhead_VarDeclaration(tokens) || LookAhead_FuncDeclaration(tokens) || LookAhead_TypeDeclaration(tokens);
}
AbstractDeclarationNode* PredictiveParser::Parse_Declaration(TokenList* tokens)
{
    if (LookAhead_FuncDeclaration(tokens)) return Parse_FuncDeclaration(tokens);
    // Parse_Declaration is only envoked in global scope, as Type and Func declarations are not allowed in local scope
    if (LookAhead_VarDeclaration(tokens)) return Parse_VarDeclaration(tokens, false);
    return Parse_TypeDeclaration(tokens);
}

bool PredictiveParser::LookAhead_VarDeclaration(TokenList* tokens)
{
    // <VarDeclarationAttributes> | ID ID !(
    if (LookAhead_VarDeclarationAttributes(tokens)) return true;

    return tokens->IsPeekOfTokenType(Tokens.CONST_IDENTIFIER_TOKEN) &&     // ID
           tokens->IsPeekOfTokenType(Tokens.CONST_IDENTIFIER_TOKEN, 1) &&  // ID
           !tokens->IsPeekOfTokenType(Tokens.PARENTHESIS_OPEN_TOKEN, 2);   // !(
}
AbstractVarDeclarationNode* PredictiveParser::Parse_VarDeclaration(TokenList* tokens, bool isLocal)
{
    VarDeclarationAttributes attributes = Parse_VarDeclarationAttributes(tokens);
    TypeNode type = TypeNode(ConsumeNext(tokens, Tokens.CONST_IDENTIFIER_TOKEN)->GetValue());
    std::string name = ConsumeNext(tokens, Tokens.CONST_IDENTIFIER_TOKEN)->GetValue();
    AbstractExpressionNode* value = nullptr;

    if (tokens->IsPeekOfTokenType(Tokens.ASSIGN_OPERATOR_TOKEN))
    {
        // Directly consuming as IsPeekOfTokenType has already checked for this token
        tokens->Next();  // Consume ASSIGN_OPERATOR
        value = Parse_Expression(tokens);
    }

    ConsumeNext(tokens, Tokens.STATEMENT_END_TOKEN);  // Consume STATEMENT_END

    if (isLocal)
    {
        return new LocalVarDeclarationNode(attributes, type, name, value);
    }
    else
    {
        return new GlobalVarDeclarationNode(attributes, type, name, value);
    }
}

bool PredictiveParser::LookAhead_FuncDeclaration(TokenList* tokens)
{
    // VOID
    if (tokens->IsPeekOfTokenType(Tokens.VOID_KEYWORD)) return true;

    // ID ID (
    return tokens->IsPeekOfTokenType(Tokens.CONST_IDENTIFIER_TOKEN) &&     // ID
           tokens->IsPeekOfTokenType(Tokens.CONST_IDENTIFIER_TOKEN, 1) &&  // ID
           tokens->IsPeekOfTokenType(Tokens.PARENTHESIS_OPEN_TOKEN, 2);    // (
}
FuncDeclarationNode* PredictiveParser::Parse_FuncDeclaration(TokenList* tokens)
{
    FunctionReturnTypeNode returnType = Parse_FunctionReturnType(tokens);

    std::string name = ConsumeNext(tokens, Tokens.CONST_IDENTIFIER_TOKEN)->GetValue();

    ConsumeNext(tokens, Tokens.PARENTHESIS_OPEN_TOKEN);  // Consume PARENTHESIS_OPEN

    std::vector<ParameterDeclarationNode*>* parameters = Parse_Params(tokens);

    ConsumeNext(tokens, Tokens.PARENTHESIS_CLOSE_TOKEN);  // Consume PARENTHESIS_CLOSE

    BodyNode* body = Parse_Body(tokens);

    return new FuncDeclarationNode(returnType, name, parameters, body);
}

bool LookAhead_FunctionReturnType(TokenList* tokens)
{
    // VOID | ID
    return tokens->IsPeekOfTokenType(Tokens.VOID_KEYWORD) || tokens->IsPeekOfTokenType(Tokens.CONST_IDENTIFIER_TOKEN);
}
FunctionReturnTypeNode PredictiveParser::Parse_FunctionReturnType(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(Tokens.VOID_KEYWORD))
    {
        // Directly consuming as IsPeekOfTokenType has already checked for this token
        tokens->Next();  // Consume VOID
        return FunctionReturnTypeNode("void");
    }

    return FunctionReturnTypeNode(tokens->Next<TokenWithValue>()->GetValue());
}

bool PredictiveParser::LookAhead_VarDeclarationAttributes(TokenList* tokens)
{
    // <final> | <inline>
    return LookAhead_FinalAttribute(tokens) || LookAhead_InlineAttribute(tokens);
}
VarDeclarationAttributes PredictiveParser::Parse_VarDeclarationAttributes(TokenList* tokens)
{
    VarDeclarationAttributes attributes;

    if (LookAhead_FinalAttribute(tokens))
    {
        attributes.isFinal = Parse_FinalAttribute(tokens);
    }

    if (LookAhead_InlineAttribute(tokens))
    {
        attributes.isInline = Parse_InlineAttribute(tokens);
    }

    return attributes;
}

bool PredictiveParser::LookAhead_TypeDeclaration(TokenList* tokens) { return tokens->IsPeekOfTokenType(Tokens.TYPEDEF_KEYWORD); }
TypeDeclarationNode* PredictiveParser::Parse_TypeDeclaration(TokenList* tokens)
{
    ConsumeNext(tokens, Tokens.TYPEDEF_KEYWORD);    // Consume TYPEDEF_KEYWORD
    ConsumeNext(tokens, Tokens.BRACES_OPEN_TOKEN);  // Consume BRACES_OPEN_TOKEN

    TypeDefCodeNode* typeDefCode = Parse_TypeDefCode(tokens);

    ConsumeNext(tokens, Tokens.BRACES_CLOSE_TOKEN);  // Consume BRACES_CLOSE_TOKEN

    std::string name = ConsumeNext(tokens, Tokens.CONST_IDENTIFIER_TOKEN)->GetValue();

    ConsumeNext(tokens, Tokens.STATEMENT_END_TOKEN);  // Consume STATEMENT_END_TOKEN

    return new TypeDeclarationNode(name, typeDefCode);
}

bool PredictiveParser::LookAhead_PropertyDeclaration(TokenList* tokens)
{
    // ID ID
    return tokens->IsPeekOfTokenType(Tokens.CONST_IDENTIFIER_TOKEN) && tokens->IsPeekOfTokenType(Tokens.CONST_IDENTIFIER_TOKEN, 1);
}
PropertyDeclarationNode* PredictiveParser::Parse_PropertyDeclaration(TokenList* tokens)
{
    TypeNode type = TypeNode(ConsumeNext(tokens, Tokens.CONST_IDENTIFIER_TOKEN)->GetValue());
    std::string name = ConsumeNext(tokens, Tokens.CONST_IDENTIFIER_TOKEN)->GetValue();

    ConsumeNext(tokens, Tokens.STATEMENT_END_TOKEN);  // Consume STATEMENT_END

    return new PropertyDeclarationNode(type, name);
}

bool PredictiveParser::LookAhead_Params(TokenList* tokens)
{
    // <paramDeclaration> (SEPERATOR <paramDeclaration>)* can be empty, therefore always true
    return true;
}
std::vector<ParameterDeclarationNode*>* PredictiveParser::Parse_Params(TokenList* tokens)
{
    std::vector<ParameterDeclarationNode*>* parameters = new std::vector<ParameterDeclarationNode*>();

    if (LookAhead_ParamDeclaration(tokens) != true)
    {
        return parameters;
    }

    parameters->push_back(Parse_ParamDeclaration(tokens));  // Parse first parameter

    // (SEPERATOR <paramDeclaration>)*
    while (tokens->IsPeekOfTokenType(Tokens.SEPERATOR_TOKEN))
    {
        ConsumeNext(tokens, Tokens.SEPERATOR_TOKEN);            // Consume seperator
        parameters->push_back(Parse_ParamDeclaration(tokens));  // Parse next parameter
    }

    return parameters;
}

bool PredictiveParser::LookAhead_ParamDeclaration(TokenList* tokens)
{
    // <final> | ID ID
    if (tokens->IsPeekOfTokenType(Tokens.FINAL_KEYWORD)) return true;

    return tokens->IsPeekOfTokenType(Tokens.CONST_IDENTIFIER_TOKEN) && tokens->IsPeekOfTokenType(Tokens.CONST_IDENTIFIER_TOKEN, 1);
}
ParameterDeclarationNode* PredictiveParser::Parse_ParamDeclaration(TokenList* tokens)
{
    bool isFinal = false;

    if (LookAhead_FinalAttribute(tokens))
    {
        Parse_FinalAttribute(tokens);
        isFinal = true;
    }

    std::string type = ConsumeNext(tokens, Tokens.CONST_IDENTIFIER_TOKEN)->GetValue();

    return new ParameterDeclarationNode(isFinal, type, ConsumeNext(tokens, Tokens.CONST_IDENTIFIER_TOKEN)->GetValue());
}

bool PredictiveParser::LookAhead_Body(TokenList* tokens)
{
    // BRACES_OPEN
    return tokens->IsPeekOfTokenType(Tokens.BRACES_OPEN_TOKEN);
}
BodyNode* PredictiveParser::Parse_Body(TokenList* tokens)
{
    BodyNode* bodynode = new BodyNode();

    ConsumeNext(tokens, Tokens.BRACES_OPEN_TOKEN);  // Consume BODY_OPEN

    while (!tokens->IsPeekOfTokenType(Tokens.BRACES_CLOSE_TOKEN))
    {
        bodynode->AddCodeLine(Parse_Line(tokens));
    }

    ConsumeNext(tokens, Tokens.BRACES_CLOSE_TOKEN);  // Consume BODY_CLOSE

    return bodynode;
}

bool PredictiveParser::LookAhead_FinalAttribute(TokenList* tokens)
{
    // FINAL
    return tokens->IsPeekOfTokenType(Tokens.FINAL_KEYWORD);
}
bool PredictiveParser::Parse_FinalAttribute(TokenList* tokens)
{
    tokens->Next();  // Consume FINAL
    return true;     // As LookAhead_FinalAttribute() has returned true, we know that final must be present
}

bool PredictiveParser::LookAhead_InlineAttribute(TokenList* tokens)
{
    // INLINE
    return tokens->IsPeekOfTokenType(Tokens.INLINE_KEYWORD);
}
bool PredictiveParser::Parse_InlineAttribute(TokenList* tokens)
{
    tokens->Next();  // Consume INLINE
    return true;     // As LookAhead_InlineAttribute() has returned true, we know that inline must be present
}
