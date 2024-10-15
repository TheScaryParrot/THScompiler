#pragma once

#include <string>

enum class EAssignOperators
{
    ASSIGN,
    ADD_ASSIGN,
    SUB_ASSIGN,
    MUL_ASSIGN,
    DIV_ASSIGN,
    MOD_ASSIGN
};

std::string EAssignOperatorsToString(EAssignOperators assignOperator)
{
    switch (assignOperator)
    {
        case EAssignOperators::ASSIGN:
            return "=";
        case EAssignOperators::ADD_ASSIGN:
            return "+=";
        case EAssignOperators::SUB_ASSIGN:
            return "-=";
        case EAssignOperators::MUL_ASSIGN:
            return "*=";
        case EAssignOperators::DIV_ASSIGN:
            return "/=";
        case EAssignOperators::MOD_ASSIGN:
            return "%=";
    }

    throw "Couldn't convert EAssignOperators to String in EAssignOperatorsToString(). Did you forget to update EAssignOperatorsToString()";
}