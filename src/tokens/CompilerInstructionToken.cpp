#pragma once

#include <string>

#include "Token.cpp"

class CompilerInstructionToken : public Token
{
   public:
    CompilerInstructionToken(std::string instruction, unsigned int line) : Token("compilerInstruction", line) { this->instruction = instruction; }

    virtual bool IsThisToken(Token& other) override
    {
        return this->Token::IsThisToken(other) && this->IsThisInstruction(dynamic_cast<CompilerInstructionToken&>(other).instruction);
    }

    bool IsThisInstruction(std::string instruction) { return this->instruction == instruction; }

    virtual bool IsCompilerInstruction() override { return true; }

    CompilerInstructionToken* New(unsigned int line) { return new CompilerInstructionToken(this->instruction, line); }

    virtual std::string ToString() override { return Token::ToString() + " " + this->instruction; }

   private:
    std::string instruction;
};