#pragma once

#include <string>

#include "Token.cpp"

class TokenWithValue : public Token
{
   public:
    TokenWithValue(std::string tokenName, unsigned int line, std::string value) : Token(tokenName, line) { this->value = value; };

    std::string GetValue() { return value; };

    TokenWithValue* New(std::string value, unsigned int line) { return new TokenWithValue(this->tokenName, line, value); };

    virtual std::string ToString() override { return Token::ToString() + " " + value; };

   private:
    std::string value;
};