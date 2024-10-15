#pragma once

#include <map>

#include "../Function.cpp"
#include "../Variable.cpp"
#include "../types/Type.cpp"

class Environment
{
   private:
    std::map<std::string, std::shared_ptr<Variable>> variables;
    std::map<std::string, std::shared_ptr<Function>> functions;
    std::map<std::string, std::shared_ptr<Type>> types;
    std::map<std::string, std::string> jumpLabels;

   public:
    unsigned int* localVariableOffset;  // Stores local variable offset
    Environment(unsigned int localVariableOffset) { this->localVariableOffset = new unsigned int(localVariableOffset); }
    ~Environment() { delete localVariableOffset; }

    bool HasVariable(std::string variableName) { return variables.find(variableName) != variables.end(); }
    std::shared_ptr<Variable> GetVariable(std::string variableName) { return variables[variableName]; }
    void AddVariable(std::string variableName, std::shared_ptr<Variable> variable) { variables[variableName] = variable; }

    bool HasType(std::string typeName) { return types.find(typeName) != types.end(); }
    std::shared_ptr<Type> GetType(std::string typeName) { return types[typeName]; }
    void AddType(std::string typeName, std::shared_ptr<Type> type) { types[typeName] = type; }

    bool HasFunction(std::string functionName) { return functions.find(functionName) != functions.end(); }
    std::shared_ptr<Function> GetFunction(std::string functionName) { return functions[functionName]; }
    void AddFunction(std::string functionName, std::shared_ptr<Function> function) { functions[functionName] = function; }

    bool HasJumpLabel(std::string labelName) { return jumpLabels.find(labelName) != jumpLabels.end(); }
    std::string GetJumpLabel(std::string labelName) { return jumpLabels[labelName]; }
    void AddJumpLabel(std::string labelName, std::string label) { jumpLabels[labelName] = label; }
};