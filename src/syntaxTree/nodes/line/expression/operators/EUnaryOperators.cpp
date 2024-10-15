#pragma once

#include <string>

enum EPreUnaryOperators
{
    PRE_NONE,
    PRE_NEGATE,
    PRE_NOT,
    PRE_INCREMENT,
    PRE_DECREMENT
};

std::string EPreUnaryOperatorsToString(EPreUnaryOperators unaryOperator)
{
    switch (unaryOperator)
    {
        case EPreUnaryOperators::PRE_NONE:
            return "";
        case EPreUnaryOperators::PRE_NEGATE:
            return "-";
        case EPreUnaryOperators::PRE_NOT:
            return "!";
        case EPreUnaryOperators::PRE_INCREMENT:
            return "++";
        case EPreUnaryOperators::PRE_DECREMENT:
            return "--";
    }

    throw "Couldn't convert EPreUnaryOperators to String in EPreUnaryOperatorsToString(). Did you forget to update EPreUnaryOperatorsToString()";
}

enum EPostUnaryOperators
{
    POST_NONE,
    POST_INCREMENT,
    POST_DECREMENT
};

std::string EPostUnaryOperatorsToString(EPostUnaryOperators unaryOperator)
{
    switch (unaryOperator)
    {
        case EPostUnaryOperators::POST_NONE:
            return "";
        case EPostUnaryOperators::POST_INCREMENT:
            return "++";
        case EPostUnaryOperators::POST_DECREMENT:
            return "--";
    }

    throw "Couldn't convert EPostUnaryOperators to String in EPostUnaryOperatorsToString(). Did you forget to update EPostUnaryOperatorsToString()";
}