#include <iostream>
#include <vector>
#include <string>
#include <filesystem>


#include "FileItem.h"
#include "FileTree.h"
#include "ClassCode.h"
#include "x64_autogen.h"
#include "CppCodeGen.h"
#include "ResCodeGenerator.h"

using std::cout; using std::cin;
using std::endl; using std::string;
using std::filesystem::directory_iterator;
namespace fs = std::filesystem;
int main(int argc, char** argv)
{

    if(argc == 0)
    {
        return EXIT_FAILURE;
    }

    std::filesystem::path executable(argv[0]);
    std::filesystem::path exeFolder = executable.parent_path();

    std::filesystem::path relativeFolder = exeFolder;
    std::filesystem::path outputFolder = exeFolder;
    std::filesystem::path resourcesFolder = exeFolder;
    bool isAbsolute = false;

    if(argc > 1)
    {
        resourcesFolder = fs::path(argv[1]);
    }
    if(argc > 2)
    {
        relativeFolder = fs::path(argv[2]);
    }
    if(argc > 3)
    {
        outputFolder = fs::path(argv[3]);
    }

    FileTree resources(resourcesFolder,relativeFolder);

    CppCodeGen cppcode;
    ResFileName naming;
    ClassCodeGenerator codeGenerator(&cppcode, &naming);

    codeGenerator.generateCode(&resources,outputFolder);

    return EXIT_SUCCESS;
}