#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <filesystem>



using std::string;
using std::unique_ptr;
using std::vector;
using namespace std::filesystem;

class FileItem
{
public:
    FileItem(directory_entry entry)
    {
        file_path = entry.path();
        std::cout << file_path << std::endl;

        if(entry.is_directory())
        {
            for(const auto& new_file : directory_iterator(file_path))
            {
                files.push_back(FileItem(new_file));
            }
        }
    }
    inline bool isFile()
    {
        return files.size() == 0;
    }
    inline bool isFolder()
    {
        return files.size() > 0;
    }
private:
    path file_path;
    vector<FileItem> files;

};

