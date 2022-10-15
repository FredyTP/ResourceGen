#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <memory>

#include "FileItem.h"
#include "FileTree.h"
#include "ClassCode.h"
#include "x64_autogen.h"
#include "CppCodeGen.h"
#include "ResCodeGenerator.h"
#include "JavaCodeGen.h"

using std::cout; using std::cin;
using std::endl; using std::string;
using std::filesystem::directory_iterator;
namespace fs = std::filesystem;
int main(int argc, char** argv)
{
    std::cout << "WELCOME TO RESOURCE CODE GENERATION SCRIPT" << std::endl;
    if(argc == 0)
    {
        std::cout << "must provide atleast 1 arg" << std::endl;
        return EXIT_FAILURE;
    }

    std::filesystem::path executable(argv[0]);
    executable = fs::absolute(executable);
    std::filesystem::path exeFolder = executable.parent_path();

    std::filesystem::path relativeFolder = exeFolder;
    std::filesystem::path outputFolder = exeFolder;
    std::filesystem::path resourcesFolder = exeFolder;
    bool isAbsolute = false;
    std::string language;
    std::string atribute;
    if(argc > 1)
    {
        language = argv[1];
    }
    if(argc > 2)
    {
        atribute = argv[2];
    }
    if(argc > 3)
    {
        resourcesFolder = fs::path(argv[3]);
    }
    if(argc > 4)
    {
        relativeFolder = fs::path(argv[4]);
    }
    if(argc > 5)
    {
        outputFolder = fs::path(argv[5]);
    }

    FileTree resources(resourcesFolder,relativeFolder);

    unique_ptr<CodeGenerator> codegen;
    unique_ptr<ResFileName> namegen;



    if(language == "java")
    {
        std::string package = atribute;
        if(package.empty())
        {
            std::cout << "Must specify package name" << std::endl;
            return EXIT_FAILURE;
        }
        std::cout << " GENERATING FOR JAVA" << std::endl;
        codegen = std::make_unique<JavaCodeGen>(package);
        namegen = std::make_unique<JavaFileName>();
    }
    else if(language == "cpp")
    {
        std::cout << " GENERATING FOR C++" << std::endl;
        codegen = std::make_unique<CppCodeGen>();
        namegen = std::make_unique<CppFileName>();
    }
    else
    {
        std::cout << " GENERATING FOR C++" << std::endl;
        codegen = std::make_unique<CppCodeGen>();
        namegen = std::make_unique<CppFileName>();
    }
    ClassCodeGenerator codeGenerator(codegen.get(), namegen.get());

    codeGenerator.generateCode(&resources,outputFolder);

    return EXIT_SUCCESS;
}