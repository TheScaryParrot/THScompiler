#pragma once

#include "Environment.cpp"

class EnvironmentLinkedList
{
   private:
    struct EnvironmentLinkedListElement
    {
        Environment* environment;
        EnvironmentLinkedListElement* next;
    };

    EnvironmentLinkedListElement* head;

   public:
    ~EnvironmentLinkedList()
    {
        while (head != nullptr)
        {
            PopEnvironment();
        }
    }

    bool DoesVariableExist(std::string variableName)
    {
        EnvironmentLinkedListElement* current = head;
        while (current != nullptr)
        {
            if (current->environment->HasVariable(variableName))
            {
                return true;
            }

            current = current->next;
        }

        return false;
    }
    std::shared_ptr<Variable> GetVariable(std::string variableName)
    {
        EnvironmentLinkedListElement* current = head;
        while (current != nullptr)
        {
            if (current->environment->HasVariable(variableName))
            {
                return current->environment->GetVariable(variableName);
            }

            current = current->next;
        }

        return nullptr;
    }
    void AddVariable(std::string variableName, std::shared_ptr<Variable> variable) { head->environment->AddVariable(variableName, variable); }

    bool DoesFunctionExist(std::string functionName)
    {
        EnvironmentLinkedListElement* current = head;
        while (current != nullptr)
        {
            if (current->environment->HasFunction(functionName))
            {
                return true;
            }

            current = current->next;
        }

        return false;
    }
    std::shared_ptr<Function> GetFunction(std::string functionName)
    {
        EnvironmentLinkedListElement* current = head;
        while (current != nullptr)
        {
            if (current->environment->HasFunction(functionName))
            {
                return current->environment->GetFunction(functionName);
            }

            current = current->next;
        }

        return nullptr;
    }
    void AddFunction(std::string functionName, std::shared_ptr<Function> function) { head->environment->AddFunction(functionName, function); }

    bool DoesTypeExist(std::string typeName)
    {
        EnvironmentLinkedListElement* current = head;
        while (current != nullptr)
        {
            if (current->environment->HasType(typeName))
            {
                return true;
            }

            current = current->next;
        }

        return false;
    }
    std::shared_ptr<Type> GetType(std::string typeName)
    {
        EnvironmentLinkedListElement* current = head;
        while (current != nullptr)
        {
            if (current->environment->HasType(typeName))
            {
                return current->environment->GetType(typeName);
            }

            current = current->next;
        }

        return nullptr;
    }
    void AddType(std::string typeName, std::shared_ptr<Type> type) { head->environment->AddType(typeName, type); }

    bool DoesJumpLabelExist(std::string labelName)
    {
        EnvironmentLinkedListElement* current = head;
        while (current != nullptr)
        {
            if (current->environment->HasJumpLabel(labelName))
            {
                return true;
            }

            current = current->next;
        }

        return false;
    }
    std::string GetJumpLabel(std::string labelName)
    {
        EnvironmentLinkedListElement* current = head;
        while (current != nullptr)
        {
            if (current->environment->HasJumpLabel(labelName))
            {
                return current->environment->GetJumpLabel(labelName);
            }

            current = current->next;
        }

        return "";
    }
    void AddJumpLabel(std::string labelName, std::string label) { head->environment->AddJumpLabel(labelName, label); }

    unsigned int* GetLocalVariableOffset() { return head->environment->localVariableOffset; }

    void PushEnvironment(Environment* environment)
    {
        EnvironmentLinkedListElement* newElement = new EnvironmentLinkedListElement();
        newElement->environment = environment;
        newElement->next = head;
        head = newElement;
    }

    void PopEnvironment()
    {
        EnvironmentLinkedListElement* newHead = head->next;

        delete head->environment;
        delete head;

        head = newHead;
    }
};