#pragma once

#include <memory>
#include <queue>
#include <string>
#include <vector>

#include "DataDeclarationLine.cpp"
#include "IAssemblyLine.cpp"

class AssemblyCode
{
   public:
    ~AssemblyCode()
    {
        while (!text.empty())
        {
            delete text.front();
            text.pop();
        }

        while (!bss.empty())
        {
            delete bss.front();
            bss.pop();
        }

        while (!data.empty())
        {
            delete data.front();
            data.pop();
        }

        while (!roData.empty())
        {
            delete roData.front();
            roData.pop();
        }
    }

    void AddLine(IAssemblyLine* line)
    {
        if (line == nullptr) return;

        this->text.push(line);
    }

    void AddToBss(DataDeclarationLine* line)
    {
        if (line == nullptr) return;

        this->bss.push(line);
    }

    void AddToRoData(DataDeclarationLine* line)
    {
        if (line == nullptr) return;

        this->roData.push(line);
    }

    void AddToData(DataDeclarationLine* line)
    {
        if (line == nullptr) return;

        this->data.push(line);
    }

    std::string ToString()
    {
        std::string result = "";

        result += "section .text\n";
        while (!text.empty())
        {
            result += text.front()->ToString() + "\n";
            delete text.front();
            text.pop();
        }

        result += "section .bss\n";
        while (!bss.empty())
        {
            result += bss.front()->ToString() + "\n";
            delete bss.front();
            bss.pop();
        }

        result += "section .data\n";
        while (!data.empty())
        {
            result += data.front()->ToString() + "\n";
            delete data.front();
            data.pop();
        }

        result += "section .rodata\n";
        while (!roData.empty())
        {
            result += roData.front()->ToString() + "\n";
            delete roData.front();
            roData.pop();
        }

        return result;
    };

   private:
    std::queue<IAssemblyLine*> text;
    std::queue<DataDeclarationLine*> bss;
    std::queue<DataDeclarationLine*> roData;
    std::queue<DataDeclarationLine*> data;
};