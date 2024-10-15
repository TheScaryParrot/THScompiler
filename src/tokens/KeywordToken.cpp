#pragma once

#include <string>

#include "Token.cpp"

class KeywordToken : public Token
{
   public:
    KeywordToken(std::string keyword, unsigned int line) : Token("keyword", line) { this->keyword = keyword; }

    virtual bool IsThisToken(Token& other) override
    {
        return this->Token::IsThisToken(other) && this->IsThisKeyword(dynamic_cast<KeywordToken&>(other).keyword);
    }

    bool IsThisKeyword(std::string keyword) { return this->keyword == keyword; }

    virtual bool IsInstruction() override { return true; }

    KeywordToken* New(unsigned int line) { return new KeywordToken(this->keyword, line); }

    virtual std::string ToString() override { return Token::ToString() + " " + this->keyword; }

   private:
    std::string keyword;
};