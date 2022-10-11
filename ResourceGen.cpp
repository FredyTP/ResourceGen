#include <iostream>
#include <vector>
#include <string>
#include <filesystem>


#include "FileItem.h"

using std::cout; using std::cin;
using std::endl; using std::string;
using std::filesystem::directory_iterator;

int main()
{
    string path = "./";
    std::filesystem::directory_entry base(path);
    FileItem file_tree(base);
    

    

    return EXIT_SUCCESS;
}