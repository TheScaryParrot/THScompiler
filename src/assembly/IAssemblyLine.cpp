#pragma once

#include <string>

class IAssemblyLine
{
   public:
    virtual ~IAssemblyLine() = default;

    virtual std::string ToString() = 0;
};