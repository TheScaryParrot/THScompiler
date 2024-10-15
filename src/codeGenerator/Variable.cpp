#pragma once

#include <memory>

#include "types/Type.cpp"
#include "varLocation/IVariableLocation.cpp"

/// @brief Represents a variable in the code generator. Contains a location, type, and whether the variable is final.
class Variable
{
   public:
    Variable(std::shared_ptr<IVariableLocation> location, std::shared_ptr<Type> type, bool isFinal)
    {
        this->location = location;
        this->type = type;
        this->isFinal = isFinal;
    }

    std::shared_ptr<IVariableLocation> location;
    std::shared_ptr<Type> type;
    bool isFinal;

    bool IsInline() { return location->IsInline(); }

    std::string ToString() { return "Variable: " + std::to_string(type->GetSize()) + " " + location->ToAssemblyString(); }
};