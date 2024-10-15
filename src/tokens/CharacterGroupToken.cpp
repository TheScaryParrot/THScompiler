#pragma once

#include "Token.cpp"

class CharacterGroupToken : public Token
{
   public:
    CharacterGroupToken(std::string tokenName, unsigned int line, CharacterGroup* characterGroup) : Token(tokenName, line)
    {
        this->characterGroup = characterGroup;
    }

    unsigned int Match(char first, char second) { return characterGroup->Match(first, second); }

    CharacterGroupToken* New(unsigned int line) { return new CharacterGroupToken(this->tokenName, line, this->characterGroup); }

   private:
    CharacterGroup* characterGroup;
};