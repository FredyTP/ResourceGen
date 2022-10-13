#pragma once

#include <string>
#include "FileItem.h"
#include <memory>

using std::string;
class FileTree
{
public:
    FileTree(std::filesystem::path folderPath,std::filesystem::path base_folder)
    {
        //Make sure folderpath is actually a path to a folder and not a file
        std::filesystem::directory_entry base(folderPath); 

        folder = std::make_unique<FileItem>(base,base_folder);
    }

    const FileItem* root() const 
    {
        return folder.get();
    }
private:
    std::unique_ptr<FileItem> folder;

};

