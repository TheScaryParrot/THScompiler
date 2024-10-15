#pragma once

#include <map>
#include <string>

#include "../../utils/Logger.cpp"
#include "../Variable.cpp"
#include "../varLocation/RegistryPointerVarLocation.cpp"
#include "Type.cpp"

class Property
{
   public:
    std::shared_ptr<Type> type;
    unsigned int offset;

    Property(std::shared_ptr<Type> type, unsigned int offset)
    {
        this->type = type;
        this->offset = offset;
    }
    Property() = default;

    std::shared_ptr<Variable> GetFromStructLocation(std::shared_ptr<IVariableLocation> location)
    {
        RegistryPointerVarLocation* newLocation = dynamic_cast<RegistryPointerVarLocation*>(location->Clone());

        if (newLocation == nullptr)
        {
            Logger.Log("Cannot apply property to non-registry pointer location " + location->ToAssemblyString(), Logger::ERROR);
            return nullptr;
        }

        newLocation->IncrementOffset(-offset);

        return std::shared_ptr<Variable>(new Variable(std::shared_ptr<IVariableLocation>(newLocation), type, false));
    }
};

class StructType : public Type
{
   private:
    unsigned int size;
    std::vector<Property> properties;               // List of properties in the order they were added
    std::map<std::string, size_t> propertyIndexes;  // Map of property names to their index in the properties vector

   public:
    StructType() { size = 0; }

    Property AddProperty(const std::string name, std::shared_ptr<Type> type)
    {
        Property property = Property(type, size);
        propertyIndexes[name] = properties.size();
        properties.push_back(property);
        size += type->GetSize();
        return property;
    }

    /// @brief Returns a Variable to the property with the given name from the given struct location
    inline std::shared_ptr<Variable> GetProperty(const std::string name, std::shared_ptr<IVariableLocation> structBaseLocation)
    {
        const size_t index = propertyIndexes[name];
        return properties[index].GetFromStructLocation(structBaseLocation);
    }

    virtual void GenerateAssign(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                                AssemblyCode* assemblyCode) override
    {
        for (Property property : properties)
        {
            std::shared_ptr<Variable> destinationProperty = property.GetFromStructLocation(destination);
            std::shared_ptr<Variable> sourceProperty = property.GetFromStructLocation(source);

            destinationProperty->type->GenerateAssign(destinationProperty->location, sourceProperty->location, assemblyCode);
        }
    }

    virtual void GenerateAdd(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot add two structs", Logger::ERROR);
    }
    virtual void GenerateSub(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot subtract two structs", Logger::ERROR);
    }
    virtual void GenerateMul(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot multiply two structs", Logger::ERROR);
    }
    virtual void GenerateDiv(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot divide two structs", Logger::ERROR);
    }
    virtual void GenerateMod(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot modulo two structs", Logger::ERROR);
    }

    virtual void GenerateNot(std::shared_ptr<IVariableLocation> destination, AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot not a struct", Logger::ERROR);
    }
    virtual void GenerateNeg(std::shared_ptr<IVariableLocation> destination, AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot negate a struct", Logger::ERROR);
    }
    virtual void GenerateInc(std::shared_ptr<IVariableLocation> destination, AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot increment a struct", Logger::ERROR);
    }
    virtual void GenerateDec(std::shared_ptr<IVariableLocation> destination, AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot decrement a struct", Logger::ERROR);
    }

    virtual void GenerateAnd(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot and two structs", Logger::ERROR);
    }
    virtual void GenerateOr(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                            AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot or two structs", Logger::ERROR);
    }
    virtual void GenerateEqual(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                               AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot compare two structs", Logger::ERROR);
    }
    virtual void GenerateNotEqual(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                                  AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot compare two structs", Logger::ERROR);
    }
    virtual void GenerateLess(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                              AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot compare two structs", Logger::ERROR);
    }
    virtual void GenerateLessEqual(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                                   AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot compare two structs", Logger::ERROR);
    }
    virtual void GenerateGreater(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                                 AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot compare two structs", Logger::ERROR);
    }
    virtual void GenerateGreaterEqual(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                                      AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot compare two structs", Logger::ERROR);
    }

    virtual void GenerateStackPush(std::shared_ptr<IVariableLocation> source, AssemblyCode* assemblyCode) override
    {
        for (Property property : properties)
        {
            std::shared_ptr<Variable> propertyVariable = property.GetFromStructLocation(source);
            propertyVariable->type->GenerateStackPush(propertyVariable->location, assemblyCode);
        }
    }

    virtual bool CanApplyToThis(Type* other) override
    {
        StructType* otherStruct = dynamic_cast<StructType*>(other);
        if (otherStruct == nullptr) return false;

        // Can be applied if all the properties are the same
        auto thisIterator = properties.begin();
        auto otherIterator = otherStruct->properties.begin();

        while (thisIterator != properties.end())
        {
            // other is empty but this is not
            if (otherIterator == otherStruct->properties.end()) return false;

            // Check whether the properties are the same
            // std::cout << thisIterator << " " << otherIterator->first << std::endl;
            // std::cout << thisIterator->type << " " << otherIterator->type << std::endl;
            if (!thisIterator->type->CanApplyToThis(otherIterator->type.get())) return false;
            if (thisIterator->offset != otherIterator->offset) return false;

            thisIterator++;
            otherIterator++;
        }

        // Return true if other is empty aswell
        return otherIterator == otherStruct->properties.end();
    }

    virtual unsigned int GetSize() override { return size; }
};