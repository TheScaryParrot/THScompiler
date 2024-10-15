#pragma once

#include <vector>

#include "AbstractExpressionNode.cpp"
#include "operators/EAssignOperators.cpp"
#include "values/VariableNode.cpp"

class Assignment
{
   public:
    Assignment(VariableNode* L_value, EAssignOperators assignOperator)
    {
        this->L_value = L_value;
        this->assignOperator = assignOperator;
    }

    ~Assignment() { delete L_value; }

    VariableNode* L_value;
    EAssignOperators assignOperator;
};

class AssignmentNode : public AbstractExpressionNode
{
   public:
    virtual ~AssignmentNode()
    {
        for (auto& assignment : assignments) delete assignment;

        delete value;
    }

    virtual bool RequiresAXRegister() override { return true; }

    virtual std::shared_ptr<Variable> TraverseExpression(CodeGenerator* codeGenerator, AssemblyCode* assemblyCode) override
    {
        std::shared_ptr<Variable> value = this->value->TraverseExpression(codeGenerator, assemblyCode);

        for (Assignment* assignment : this->assignments)
        {
            std::shared_ptr<Variable> l_variable = assignment->L_value->TraverseExpression(codeGenerator, assemblyCode);

            if (l_variable->isFinal)
            {
                Logger.Log("Cannot assign to final variable " + assignment->L_value->ids[0], Logger::ERROR);
                continue;
            }

            EOperators op = EOperators::ASSIGN_OPERATOR;

            switch (assignment->assignOperator)
            {
                case EAssignOperators::ASSIGN:
                    break;
                case EAssignOperators::ADD_ASSIGN:
                    op = EOperators::ADD_OPERATOR;
                    break;
                case EAssignOperators::SUB_ASSIGN:
                    op = EOperators::SUB_OPERATOR;
                    break;
                case EAssignOperators::MUL_ASSIGN:
                    op = EOperators::MUL_OPERATOR;
                    break;
                case EAssignOperators::DIV_ASSIGN:
                    op = EOperators::DIV_OPERATOR;
                    break;
                case EAssignOperators::MOD_ASSIGN:
                    op = EOperators::MOD_OPERATOR;
                    break;
            }

            codeGenerator->ApplyBinaryOperatorOnVariables(l_variable, value, op, assemblyCode);

            value = l_variable;
        }

        return value;
    }

    virtual std::string ToString() override
    {
        std::string result = "";

        for (Assignment* assignment : assignments)
        {
            result += assignment->L_value->ToString() + " " + EAssignOperatorsToString(assignment->assignOperator) + " ";
        }

        return result + value->ToString();
    }

    std::vector<Assignment*> assignments;
    AbstractExpressionNode* value;
};
