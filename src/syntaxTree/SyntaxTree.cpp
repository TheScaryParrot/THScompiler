#pragma once

#include <iostream>

#include "nodes/GlobalCodeNode.cpp"

class SyntaxTree
{
   private:
    GlobalCodeNode* code;

   public:
    SyntaxTree(GlobalCodeNode* code) { this->code = code; }
    ~SyntaxTree() { delete code; }

    GlobalCodeNode* GetCode() { return code; };

    std::string ToString() { return code->ToString(); }
};