#pragma once

#include <iostream>

#include "../tokens/CharacterGroupToken.cpp"
#include "../tokens/TokenList.cpp"
#include "../tokens/TokenWithValue.cpp"
#include "../tokens/Tokens.cpp"
#include "../tokens/characterGroups/CharacterGroups.cpp"
#include "../utils/Logger.cpp"
#include "../utils/InputFile.cpp"

static class Scanner
{
   private:
    bool TryConsumeCharacterGroup(InputFile* file, const char consumedCharacter, const char peekCharacter, CharacterGroup& characterGroup)
    {
        const unsigned int match = characterGroup.Match(consumedCharacter, peekCharacter);

        if (!match) return false;

        // Consume peekCharacter if both characters were matched
        if (match == 2) file->ReadNext();
        return true;
    }

    /// @brief If the consumed and peek character match the character group token, the token is added to the tokens list
    /// @return Whether the character group token was added
    bool TryAddCharacterGroupToken(InputFile* file, TokenList* tokens, CharacterGroupToken& token, char consumedCharacter, char peekCharacter)
    {
        unsigned int match = token.Match(consumedCharacter, peekCharacter);

        if (match == 0) return false;

        tokens->AddToken(token.New(lineCounter));

        if (match == 2) file->ReadNext();  // As the peek character matched aswell we need to consume it

        return true;
    }

    /// @brief If the given identifier corresponds to the KeywordToken the KeywordToken is added
    /// @return Whether the identifier is the keyword
    bool TryAddKeywordToken(TokenList* tokens, std::string identifier, KeywordToken& token)
    {
        if (token.IsThisKeyword(identifier))
        {
            tokens->AddToken(token.New(lineCounter));
            return true;
        }

        return false;
    }

    /// @brief If the given identifier is a keyword, add the corresponding token to the tokens list
    /// @return whether the identifier is a keyword
    bool TryAddKeyword(TokenList* tokens, std::string identifier)
    {
        if (TryAddKeywordToken(tokens, identifier, Tokens.IF_KEYWORD)) return true;
        if (TryAddKeywordToken(tokens, identifier, Tokens.ELSE_KEYWORD)) return true;
        if (TryAddKeywordToken(tokens, identifier, Tokens.ELIF_KEYWORD)) return true;

        if (TryAddKeywordToken(tokens, identifier, Tokens.WHILE_KEYWORD)) return true;
        if (TryAddKeywordToken(tokens, identifier, Tokens.FOR_KEYWORD)) return true;
        if (TryAddKeywordToken(tokens, identifier, Tokens.BREAK_KEYWORD)) return true;
        if (TryAddKeywordToken(tokens, identifier, Tokens.CONTINUE_KEYWORD)) return true;

        if (TryAddKeywordToken(tokens, identifier, Tokens.LOGICAL_TRUE_KEYWORD)) return true;
        if (TryAddKeywordToken(tokens, identifier, Tokens.LOGICAL_FALSE_KEYWORD)) return true;

        if (TryAddKeywordToken(tokens, identifier, Tokens.RETURN_KEYWORD)) return true;
        if (TryAddKeywordToken(tokens, identifier, Tokens.VOID_KEYWORD)) return true;

        if (TryAddKeywordToken(tokens, identifier, Tokens.FINAL_KEYWORD)) return true;
        if (TryAddKeywordToken(tokens, identifier, Tokens.INLINE_KEYWORD)) return true;

        if (TryAddKeywordToken(tokens, identifier, Tokens.TYPEDEF_KEYWORD)) return true;

        return false;
    }

    /// @brief If the given identifier corresponds to the CompilerInstructionToken the CompilerInstructionToken is added
    /// @return Whether the identifier is the compiler instruction
    bool TryAddCompilerInstructionToken(TokenList* tokens, std::string identifier, CompilerInstructionToken& token)
    {
        if (token.IsThisInstruction(identifier))
        {
            tokens->AddToken(token.New(lineCounter));
            return true;
        }

        return false;
    }

    /// @brief If the given identifier is a compiler instruction, add the corresponding token to the tokens list
    /// @return whether the identifier is a compiler instruction
    bool TryAddCompilerInstruction(TokenList* tokens, std::string identifier)
    {
        if (TryAddCompilerInstructionToken(tokens, identifier, Tokens.EXTERN_INSTRUCTION)) return true;
        if (TryAddCompilerInstructionToken(tokens, identifier, Tokens.GLOBAL_INSTRUCTION)) return true;

        return false;
    }

    unsigned int lineCounter = 1;

   public:
    TokenList* Scan(InputFile* file)
    {
        TokenList* tokens = new TokenList();

        if (!file->IsGood()) throw "Can't scan InputFile. file is not good";

        while (!file->IsEndOfFile())
        {
            char character = file->ReadNext();
            char peekCharacter = file->PeekNext();

            if (CharacterGroups.NEWLINE.Match(character, peekCharacter))
            {
                lineCounter++;
                continue;
            }

            // Ignore whitespaces
            if (CharacterGroups.WHITESPACES.Match(character, peekCharacter)) continue;

            // --- Delimitors ---
            if (TryAddCharacterGroupToken(file, tokens, Tokens.STATEMENT_END_TOKEN, character, peekCharacter)) continue;

            if (TryAddCharacterGroupToken(file, tokens, Tokens.BRACES_OPEN_TOKEN, character, peekCharacter)) continue;
            if (TryAddCharacterGroupToken(file, tokens, Tokens.BRACES_CLOSE_TOKEN, character, peekCharacter)) continue;

            if (TryAddCharacterGroupToken(file, tokens, Tokens.PARENTHESIS_OPEN_TOKEN, character, peekCharacter)) continue;
            if (TryAddCharacterGroupToken(file, tokens, Tokens.PARENTHESIS_CLOSE_TOKEN, character, peekCharacter)) continue;

            if (TryAddCharacterGroupToken(file, tokens, Tokens.SEPERATOR_TOKEN, character, peekCharacter)) continue;

            // --- Comments ---
            if (TryConsumeCharacterGroup(file, character, peekCharacter, CharacterGroups.SINGLE_LINE_COMMENT))
            {
                while (file->PeekNext() != '\n')
                {
                    file->ReadNext();
                }

                continue;
            }

            if (TryConsumeCharacterGroup(file, character, peekCharacter, CharacterGroups.MULTI_LINE_COMMENT_START))
            {
                do
                {
                    character = file->ReadNext();
                    peekCharacter = file->PeekNext();
                } while (!TryConsumeCharacterGroup(file, character, peekCharacter, CharacterGroups.MULTI_LINE_COMMENT_END));

                continue;
            }

            // --- Number ---
            if (CharacterGroups.NUMBERS.Match(character, peekCharacter))
            {
                std::string number = std::string(1, character);

                bool foundDot = false;

                while (CharacterGroups.NUMBER_OR_DOT.Match(file->PeekNext(),
                                                           0))  // INFO: It's a bit of a hack to pass 0 as the second argument; but should work
                {
                    if (file->PeekNext() == '.')
                    {
                        if (foundDot)
                        {
                            std::cerr << "Invalid number format. Multiple dots in number\n";
                            break;
                        }

                        foundDot = true;
                    }

                    number += file->ReadNext();
                }

                if (foundDot)
                {
                    tokens->AddToken(Tokens.CONST_FLOAT_TOKEN.New(number, lineCounter));
                }
                else
                {
                    tokens->AddToken(Tokens.CONST_INT_TOKEN.New(number, lineCounter));
                }

                continue;
            }

            // --- String ---
            if (TryConsumeCharacterGroup(file, character, peekCharacter, CharacterGroups.STRING_DELIMITOR))
            {
                std::string string = "";

                while (true)
                {
                    character = file->ReadNext();      // Read next
                    peekCharacter = file->PeekNext();  // Peek next

                    if (TryConsumeCharacterGroup(file, character, peekCharacter, CharacterGroups.STRING_DELIMITOR))
                    {
                        break;
                    }

                    string += character;
                }

                tokens->AddToken(Tokens.CONST_STRING_TOKEN.New(string, lineCounter));

                continue;
            }

            // --- Identifier ---
            if (CharacterGroups.IDENTIFIER_START_CHAR.Match(character, peekCharacter))
            {
                std::string identifierString = std::string(1, character);

                while (CharacterGroups.IDENTIFIER_CHAR.Match(file->PeekNext(), 0))
                {
                    identifierString += file->ReadNext();
                }

                // Check whether the identifier is a keyword
                if (TryAddKeyword(tokens, identifierString)) continue;

                // Check whether the identifier is a compiler instruction
                if (TryAddCompilerInstruction(tokens, identifierString)) continue;

                tokens->AddToken(Tokens.CONST_IDENTIFIER_TOKEN.New(identifierString, lineCounter));
                continue;
            }

            if (TryAddCharacterGroupToken(file, tokens, Tokens.DOT_TOKEN, character, peekCharacter)) continue;

            // --- Equal Operators ---

            if (TryAddCharacterGroupToken(file, tokens, Tokens.EQUAL_OPERATOR_TOKEN, character, peekCharacter)) continue;
            if (TryAddCharacterGroupToken(file, tokens, Tokens.NOT_EQUAL_OPERATOR_TOKEN, character, peekCharacter)) continue;
            // less/greater or equal operators must be checked before less/greater operators as otherwise they are parsed as two separate tokens
            if (TryAddCharacterGroupToken(file, tokens, Tokens.GREATER_THAN_OR_EQUAL_OPERATOR_TOKEN, character, peekCharacter)) continue;
            if (TryAddCharacterGroupToken(file, tokens, Tokens.LESS_THAN_OR_EQUAL_OPERATOR_TOKEN, character, peekCharacter)) continue;
            if (TryAddCharacterGroupToken(file, tokens, Tokens.GREATER_THAN_OPERATOR_TOKEN, character, peekCharacter)) continue;
            if (TryAddCharacterGroupToken(file, tokens, Tokens.LESS_THAN_OPERATOR_TOKEN, character, peekCharacter)) continue;

            // --- Assign Operators ---
            if (TryAddCharacterGroupToken(file, tokens, Tokens.ASSIGN_OPERATOR_TOKEN, character, peekCharacter)) continue;
            if (TryAddCharacterGroupToken(file, tokens, Tokens.ADD_ASSIGN_OPERATOR_TOKEN, character, peekCharacter)) continue;
            if (TryAddCharacterGroupToken(file, tokens, Tokens.SUB_ASSIGN_OPERATOR_TOKEN, character, peekCharacter)) continue;
            if (TryAddCharacterGroupToken(file, tokens, Tokens.MUL_ASSIGN_OPERATOR_TOKEN, character, peekCharacter)) continue;
            if (TryAddCharacterGroupToken(file, tokens, Tokens.DIV_ASSIGN_OPERATOR_TOKEN, character, peekCharacter)) continue;
            if (TryAddCharacterGroupToken(file, tokens, Tokens.MOD_ASSIGN_OPERATOR_TOKEN, character, peekCharacter)) continue;

            // --- Increment and Decrement Operators ---
            if (TryAddCharacterGroupToken(file, tokens, Tokens.INCREMENT_OPERATOR_TOKEN, character, peekCharacter)) continue;
            if (TryAddCharacterGroupToken(file, tokens, Tokens.DECREMENT_OPERATOR_TOKEN, character, peekCharacter)) continue;

            // --- Arithmetic Operators ---
            if (TryAddCharacterGroupToken(file, tokens, Tokens.ADD_OPERATOR_TOKEN, character, peekCharacter)) continue;
            if (TryAddCharacterGroupToken(file, tokens, Tokens.SUB_OPERATOR_TOKEN, character, peekCharacter)) continue;
            if (TryAddCharacterGroupToken(file, tokens, Tokens.MUL_OPERATOR_TOKEN, character, peekCharacter)) continue;
            if (TryAddCharacterGroupToken(file, tokens, Tokens.DIV_OPERATOR_TOKEN, character, peekCharacter)) continue;
            if (TryAddCharacterGroupToken(file, tokens, Tokens.MOD_OPERATOR_TOKEN, character, peekCharacter)) continue;

            // --- Negate Operator ---
            // TODO: Issue here as this will be parsed as a sub operator
            if (TryAddCharacterGroupToken(file, tokens, Tokens.NEGATE_OPERATOR_TOKEN, character, peekCharacter)) continue;

            // --- Logical Operators ---
            if (TryAddCharacterGroupToken(file, tokens, Tokens.AND_OPERATOR_TOKEN, character, peekCharacter)) continue;
            if (TryAddCharacterGroupToken(file, tokens, Tokens.OR_OPERATOR_TOKEN, character, peekCharacter)) continue;
            if (TryAddCharacterGroupToken(file, tokens, Tokens.NOT_OPERATOR_TOKEN, character, peekCharacter)) continue;

            // --- Unknown Token ---
            Logger.Log("Unknown token: " + character, Logger::ERROR);
        }

        return tokens;
    }
} Scanner;