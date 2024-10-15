#pragma once

#include "../expression/AbstractExpressionNode.cpp"
#include "AbstractDeclarationNode.cpp"
#include "VarDeclarationAttributes.cpp"
#include "types/TypeNode.cpp"

class AbstractVarDeclarationNode : public AbstractDeclarationNode
{
   public:
    std::string name;
    TypeNode type;
    AbstractExpressionNode* value;
    VarDeclarationAttributes attributes;

    AbstractVarDeclarationNode(VarDeclarationAttributes attributes, TypeNode type, std::string name, AbstractExpressionNode* value = nullptr)
        : AbstractDeclarationNode()
    {
        this->attributes = attributes;
        this->type = type;
        this->name = name;
        this->value = value;
    }

    ~AbstractVarDeclarationNode() { delete value; }

    virtual std::string ToString() override
    {
        std::string result = attributes.ToString() + type.ToString() + " " + name;

        if (value != nullptr)
        {
            result += " = " + value->ToString();
        }

        return result + ";";
    }
};