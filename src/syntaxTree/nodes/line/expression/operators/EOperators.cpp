#pragma once

#include <string>

enum EOperators
{
    ASSIGN_OPERATOR,

    OR_OPERATOR,
    AND_OPERATOR,

    EQUAL_OPERATOR,
    NOT_EQUAL_OPERATOR,
    LESS_THAN_OPERATOR,
    GREATER_THAN_OPERATOR,
    LESS_THAN_OR_EQUAL_OPERATOR,
    GREATER_THAN_OR_EQUAL_OPERATOR,

    ADD_OPERATOR,
    SUB_OPERATOR,
    MUL_OPERATOR,
    DIV_OPERATOR,
    MOD_OPERATOR,
};

std::string EOperatorsToString(EOperators operatorValue)
{
    switch (operatorValue)
    {
        case ASSIGN_OPERATOR:
            return "=";

        case OR_OPERATOR:
            return "||";
        case AND_OPERATOR:
            return "&&";

        case EQUAL_OPERATOR:
            return "==";
        case NOT_EQUAL_OPERATOR:
            return "!=";
        case LESS_THAN_OPERATOR:
            return "<";
        case GREATER_THAN_OPERATOR:
            return ">";
        case LESS_THAN_OR_EQUAL_OPERATOR:
            return "<=";
        case GREATER_THAN_OR_EQUAL_OPERATOR:
            return ">=";

        case ADD_OPERATOR:
            return "+";
        case SUB_OPERATOR:
            return "-";
        case MUL_OPERATOR:
            return "*";
        case DIV_OPERATOR:
            return "/";
        case MOD_OPERATOR:
            return "%";
    }

    throw "Couldn't convert EOperators to String in EOperatorsToString(). Did you forget to update "
          "EOperatorsToString()";
}