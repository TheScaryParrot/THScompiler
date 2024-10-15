#pragma once

#include <fstream>

class InputFile
{
   public:
    InputFile(std::string filename) { file.open(filename); }
    ~InputFile() { file.close(); }

    /// @brief Reads the next character from the file. And advances the file pointer.
    char ReadNext() { return file.get(); }

    /// @brief Peeks the next character from the file. Doesnt advance the file pointer.
    char PeekNext() { return file.peek(); }

    bool IsEndOfFile() { return file.eof(); }
    bool IsGood() { return file.good(); }

   private:
    std::ifstream file;
};