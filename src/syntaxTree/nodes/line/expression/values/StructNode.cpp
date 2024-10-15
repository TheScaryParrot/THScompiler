#pragma once

#include <vector>

#include "AbstractValueNode.cpp"

class StructNode : public AbstractValueNode
{
   public:
    std::vector<AbstractExpressionNode*> values;

    StructNode(std::vector<AbstractExpressionNode*> values) : AbstractValueNode() { this->values = values; }

    ~StructNode()
    {
        for (auto value : values)
        {
            delete value;
        }
    }

    virtual bool RequiresAXRegister() override { return true; }

    virtual std::shared_ptr<Variable> TraverseExpression(CodeGenerator* codeGenerator, AssemblyCode* assemblyCode) override
    {
        std::shared_ptr<StructType> tempStructType = std::shared_ptr<StructType>(new StructType());

        std::vector<std::pair<Property, std::shared_ptr<Variable>>> propertyAssigns;

        // Generate temporary structtype
        for (size_t i = 0; i < this->values.size(); i++)
        {
            std::shared_ptr<Variable> r_value = this->values[i]->TraverseExpression(codeGenerator, assemblyCode);
            propertyAssigns.push_back({tempStructType->AddProperty(std::to_string(i), r_value->type), r_value});
        }

        Variable* structVariable = codeGenerator->GetNewLocalVariable(tempStructType, false, assemblyCode);

        // Assign the values to the struct
        for (size_t i = 0; i < propertyAssigns.size(); i++)
        {
            std::pair<Property, std::shared_ptr<Variable>> propertyAssign = propertyAssigns[i];
            std::shared_ptr<Variable> l_value = propertyAssign.first.GetFromStructLocation(structVariable->location);
            std::shared_ptr<Variable> r_value = propertyAssign.second;

            l_value->type->GenerateAssign(l_value->location, r_value->location, assemblyCode);
        }

        return std::shared_ptr<Variable>(structVariable);
    }

    virtual std::string ToString() override
    {
        std::string result = "{";
        for (auto value : values)
        {
            result += value->ToString() + ", ";
        }
        result += "}";
        return result;
    }
};