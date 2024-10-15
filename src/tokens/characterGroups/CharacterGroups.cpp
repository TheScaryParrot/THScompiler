#pragma once

#include <vector>

#include "CharacterGroup.cpp"

static class CharacterGroups
{
   public:
    // Newline is differenciated from whitespace to allow the scanner to count lines
    CharacterGroup NEWLINE = CharacterGroup(std::vector<TwoChar>{'\n'});
    CharacterGroup WHITESPACES = CharacterGroup(std::vector<TwoChar>{' ', '\t', '\r'});
    CharacterGroup STATEMENT_END = CharacterGroup(std::vector<TwoChar>{';'});

    CharacterGroup LOWER_ALPHABET = CharacterGroup(std::vector<TwoChar>{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                                                                        'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'});
    CharacterGroup UPPER_ALPHABET = CharacterGroup(std::vector<TwoChar>{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                                                                        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'});
    CharacterGroup ALPHABET = CharacterGroup(std::vector<TwoChar>(), std::vector<CharacterGroup>{LOWER_ALPHABET, UPPER_ALPHABET});
    CharacterGroup NUMBERS = CharacterGroup(std::vector<TwoChar>{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'});
    CharacterGroup ALPHANUMERIC = CharacterGroup(std::vector<CharacterGroup>{ALPHABET, NUMBERS});
    CharacterGroup NUMBER_OR_DOT = CharacterGroup(std::vector<TwoChar>{'.'}, std::vector<CharacterGroup>{NUMBERS});

    CharacterGroup STRING_DELIMITOR = CharacterGroup(std::vector<TwoChar>{'"', '\''});

    CharacterGroup IDENTIFIER_START_CHAR = CharacterGroup(std::vector<TwoChar>{'_'}, std::vector<CharacterGroup>{ALPHABET});
    CharacterGroup IDENTIFIER_CHAR = CharacterGroup(std::vector<TwoChar>{'_'}, std::vector<CharacterGroup>{ALPHABET, NUMBERS});

    CharacterGroup BRACES_OPEN = CharacterGroup(std::vector<TwoChar>{'{'});
    CharacterGroup BRACES_CLOSE = CharacterGroup(std::vector<TwoChar>{'}'});
    CharacterGroup PARENTHESIS_OPEN = CharacterGroup(std::vector<TwoChar>{'('});
    CharacterGroup PARENTHESIS_CLOSE = CharacterGroup(std::vector<TwoChar>{')'});
    CharacterGroup SEPERATOR = CharacterGroup(std::vector<TwoChar>{','});

    CharacterGroup EQUAL_OPERATOR = CharacterGroup(std::vector<TwoChar>{"=="});
    CharacterGroup NOT_EQUAL_OPERATOR = CharacterGroup(std::vector<TwoChar>{"!="});
    CharacterGroup GREATER_THAN_OPERATOR = CharacterGroup(std::vector<TwoChar>{'>'});
    CharacterGroup LESS_THAN_OPERATOR = CharacterGroup(std::vector<TwoChar>{'<'});
    CharacterGroup GREATER_THAN_OR_EQUAL_OPERATOR = CharacterGroup(std::vector<TwoChar>{">="});
    CharacterGroup LESS_THAN_OR_EQUAL_OPERATOR = CharacterGroup(std::vector<TwoChar>{"<="});

    CharacterGroup ADD_OPERATOR = CharacterGroup(std::vector<TwoChar>{'+'});
    CharacterGroup SUB_OPERATOR = CharacterGroup(std::vector<TwoChar>{'-'});
    CharacterGroup MUL_OPERATOR = CharacterGroup(std::vector<TwoChar>{'*'});
    CharacterGroup DIV_OPERATOR = CharacterGroup(std::vector<TwoChar>{'/'});
    CharacterGroup MOD_OPERATOR = CharacterGroup(std::vector<TwoChar>{'%'});

    CharacterGroup ASSIGN_OPERATOR = CharacterGroup(std::vector<TwoChar>{'='});
    CharacterGroup ADD_ASSIGN_OPERATOR = CharacterGroup(std::vector<TwoChar>{"+="});
    CharacterGroup SUB_ASSIGN_OPERATOR = CharacterGroup(std::vector<TwoChar>{"-="});
    CharacterGroup MUL_ASSIGN_OPERATOR = CharacterGroup(std::vector<TwoChar>{"*="});
    CharacterGroup DIV_ASSIGN_OPERATOR = CharacterGroup(std::vector<TwoChar>{"/="});
    CharacterGroup MOD_ASSIGN_OPERATOR = CharacterGroup(std::vector<TwoChar>{"%="});

    CharacterGroup INCREMENT_OPERATOR = CharacterGroup(std::vector<TwoChar>{"++"});
    CharacterGroup DECREMENT_OPERATOR = CharacterGroup(std::vector<TwoChar>{"--"});

    CharacterGroup NEGATE_OPERATOR = CharacterGroup(std::vector<TwoChar>{'-'});

    CharacterGroup NOT_OPERATOR = CharacterGroup(std::vector<TwoChar>{'!'});
    CharacterGroup AND_OPERATOR = CharacterGroup(std::vector<TwoChar>{"&&"});
    CharacterGroup OR_OPERATOR = CharacterGroup(std::vector<TwoChar>{"||"});

    CharacterGroup SINGLE_LINE_COMMENT = CharacterGroup(std::vector<TwoChar>{"//"});
    CharacterGroup MULTI_LINE_COMMENT_START = CharacterGroup(std::vector<TwoChar>{"/*"});
    CharacterGroup MULTI_LINE_COMMENT_END = CharacterGroup(std::vector<TwoChar>{"*/"});

    CharacterGroup DOT = CharacterGroup(std::vector<TwoChar>{'.'});

} CharacterGroups;