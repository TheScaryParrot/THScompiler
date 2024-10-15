#pragma once

#include <iostream>
#include <string>

static class Logger
{
   public:
    enum ELogTypes
    {
        DEBUG,
        INFO,
        WARNING,
        ERROR
    };

    void Log(std::string message, ELogTypes type)
    {
        if (!IsDebug && type == ELogTypes::DEBUG)
        {
            return;
        }

        std::cout << ConstructLogMessage(message, type) << std::endl;
    }

    void SetDebug(bool debug) { IsDebug = debug; };

   private:
    std::string ConstructLogMessage(std::string message, ELogTypes type) { return "[" + GetLogTypeString(type) + "] " + message; }
    std::string GetLogTypeString(ELogTypes type)
    {
        switch (type)
        {
            case ELogTypes::DEBUG:
                return "DEBUG";
            case ELogTypes::INFO:
                return "INFO";
            case ELogTypes::WARNING:
                return "WARNING";
            case ELogTypes::ERROR:
                return "ERROR";
        }

        return "";
    }

    bool IsDebug = false;
} Logger;