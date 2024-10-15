#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Token.cpp"

class TokenList
{
   private:
    struct Node
    {
        Token* token;
        Node* next;
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    size_t size = 0;

   public:
    ~TokenList()
    {
        Node* temp;
        while (head != nullptr)
        {
            temp = head->next;
            delete head->token;
            delete head;
            head = temp;
        }
    }

    void AddToken(Token* token)
    {
        size++;
        Node* node = new Node();
        node->token = token;
        node->next = nullptr;

        if (head == nullptr)
        {
            head = node;
            tail = node;
            return;
        }

        tail->next = node;
        tail = node;
    }
    size_t GetSize() { return size; }

    template <typename T>
    T* Next()
    {
        return dynamic_cast<T*>(Next());
    }

    Token* Next()
    {
        if (HasNext())
        {
            size--;
            Token* token = head->token;
            Node* temp = head;
            head = temp->next;
            delete temp;
            return token;
        }

        return nullptr;
    }

    Token* Peek(unsigned int offset = 0)
    {
        if (!HasNext(offset)) return nullptr;

        Node* current = head;
        for (unsigned int i = 0; i < offset; i++)
        {
            current = current->next;
        }

        return current->token;
    }
    bool IsPeekOfTokenType(Token& other, unsigned int offset = 0)
    {
        if (!HasNext(offset)) return false;

        return Peek(offset)->IsThisToken(other);
    }

    bool HasNext(unsigned int offset = 0) { return offset < size; }

    std::string ToString()
    {
        std::string result = "";
        Node* current = head;

        while (current != nullptr)
        {
            result += current->token->ToString() + " ";
            current = current->next;
        }

        return result;
    }
};