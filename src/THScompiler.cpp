#include <iostream>

#include "parser/parserDefinitions/CompilerInstructionParserDefinitions.cpp"
#include "parser/parserDefinitions/DeclarationParserDefinitions.cpp"
#include "parser/parserDefinitions/ExpressionParserDefinitions.cpp"
#include "parser/parserDefinitions/GeneralParserDefinitions.cpp"
#include "parser/parserDefinitions/StatementParserDefinitions.cpp"
#include "scanner/Scanner.cpp"
#include "utils/OutputFile.cpp"
#include "utils/argparse.hpp"  //argparser

AssemblyCode* CompileFile(std::string filename)
{
    InputFile* file = new InputFile(filename);

    // Scanning
    TokenList* tokens = Scanner.Scan(file);
    delete file;

    // Parsing
    SyntaxTree* syntaxTree = PredictiveParser.Parse(tokens);
    delete tokens;

    // std::cout << "------Syntax Tree------\n";
    // std::cout << syntaxTree->ToString() << std::endl;

    // Code generation
    AssemblyCode* assemblyCode = new AssemblyCode();
    CodeGenerator codeGenerator = CodeGenerator();
    syntaxTree->GetCode()->Traverse(&codeGenerator, assemblyCode);
    delete syntaxTree;

    return assemblyCode;
}

void OutToFile(AssemblyCode* code, std::string filename)
{
    OutputFile outFile = OutputFile(filename);
    outFile.Write(code->ToString());
}

void Assemble(std::string inFile, std::string outFile, bool deleteInFile)
{
    Logger.Log("Assembling " + inFile + " to " + outFile, Logger::INFO);

    std::string command = "nasm -felf64 " + inFile + " -o " + outFile;
    system(command.c_str());

    if (deleteInFile)
    {
        std::string command = "rm " + inFile;
        system(command.c_str());
    }
}

void Link(std::string inFile, std::string outFile, bool deleteInFile, std::vector<std::string> linkFiles)
{
    Logger.Log("Linking " + inFile + " to " + outFile, Logger::INFO);

    std::string command = "ld " + inFile;
    for (std::string linkFile : linkFiles) command += " " + linkFile;
    command += +" -o " + outFile;
    system(command.c_str());

    if (deleteInFile)
    {
        std::string command = "rm " + inFile;
        system(command.c_str());
    }
}

int main(int argc, char const* argv[])
{
    argparse::ArgumentParser program("THS compiler");

    program.add_argument("file").help("The file to compile");
    program.add_argument("-o", "--output").help("The output file. If none is specified the output will be stored in a.out").default_value("a.out");

    program.add_argument("-c", "--compile").help("Only compile, do not assemble and link").default_value(false).implicit_value(true);
    program.add_argument("-s", "--assemble").help("Only compile and assemble, do not link").default_value(false).implicit_value(true);
    program.add_argument("-k", "--keep").help("Keep temporary files").default_value(false).implicit_value(true);

    program.add_argument("--link-files")
        .help("Include files in linking process")
        .nargs(argparse::nargs_pattern::at_least_one)
        .default_value(std::vector<std::string>());

    try
    {
        program.parse_args(argc, argv);
    }
    catch (const std::runtime_error& err)
    {
        std::cout << err.what() << std::endl;
        std::cout << program;
        exit(0);
    }

    std::string filePath = program.get<std::string>("file");
    AssemblyCode* outCode = CompileFile(filePath);
    bool deleteTempFiles = !program.get<bool>("--keep");
    std::vector<std::string> linkFiles = program.get<std::vector<std::string>>("--link-files");

    if (program["--compile"] == true)
    {
        OutToFile(outCode, program.get<std::string>("--output"));
    }
    else if (program["--assemble"] == true)
    {
        OutToFile(outCode, "a.s");
        Assemble("a.s", program.get<std::string>("--output"), deleteTempFiles);
    }
    else
    {
        OutToFile(outCode, "a.s");
        Assemble("a.s", "a.o", deleteTempFiles);
        Link("a.o", program.get<std::string>("--output"), deleteTempFiles, linkFiles);
    }

    delete outCode;

    return 0;
}
