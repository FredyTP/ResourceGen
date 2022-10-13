#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <filesystem>



using std::string;
using std::unique_ptr;
using std::vector;
namespace fs = std::filesystem;

class FileItem
{
public:
    FileItem()
    {

    }
    FileItem(fs::directory_entry entry,fs::path base_directory)
    {
        relative_path = fs::relative(entry.path(), base_directory);
        absolute_path = fs::absolute(entry.path());
        std::cout << fs::absolute(entry.path()) << std::endl;

        if(entry.is_directory())
        {
            for(const auto& new_file : fs::directory_iterator(entry.path()))
            {
                files.push_back(FileItem(new_file,base_directory));
            }
        }
    }
    inline bool isFile() const
    {
        return files.size() == 0;
    }
    inline bool isFolder() const
    {
        return files.size() > 0;
    }
    inline const string name() const
    {
        if(!absolute_path.has_filename()) return "no_name";
        return absolute_path.filename().string();
    }
    const fs::path& relativePath() const
    {
        return relative_path;
    }
    const fs::path& absolutePath() const
    {
        return absolute_path;
    }
    const vector<FileItem>& subFiles() const
    {
        return files;
    }


private:
    fs::path relative_path;
    fs::path absolute_path;
    vector<FileItem> files;

};

