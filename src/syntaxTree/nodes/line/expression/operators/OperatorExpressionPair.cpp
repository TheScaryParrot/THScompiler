#pragma once

#include "../AbstractExpressionNode.cpp"
#include "EOperators.cpp"

class OperatorExpressionPair
{
   public:
    OperatorExpressionPair(EOperators op, AbstractExpressionNode* expression);
    ~OperatorExpressionPair();

    std::string ToString();

    EOperators op;  // operator
    AbstractExpressionNode* expression;
};

OperatorExpressionPair::OperatorExpressionPair(EOperators op, AbstractExpressionNode* expression)
{
    this->op = op;
    this->expression = expression;
}

OperatorExpressionPair::~OperatorExpressionPair() { delete expression; }

std::string OperatorExpressionPair::ToString() { return EOperatorsToString(op) + expression->ToString(); }