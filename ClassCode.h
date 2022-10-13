#pragma once
#include <string>
#include <fstream>

#include "FileItem.h"
#include "FileTree.h"

#include "ResCodeGenerator.h"

using std::string;
using std::endl;



class ClassCodeGenerator
{
public:
    ClassCodeGenerator(CodeGenerator* _coding, ResFileName* _naming)
    {
        this->coding = _coding;
        this->naming = _naming;
    }
    void generateCode(const FileTree* folder,std::filesystem::path outputFolder)
    {
       //getFolderPath
       const auto &path = folder->root()->absolutePath();

       //Create code file name
       const auto outputpath = outputFolder;

       string code_name = path.filename().string() + "_autogen.h";
       std::cout << outputpath.generic_string() << std::endl;
       //open file name and set the location
       code.open(outputFolder.generic_string() + "/" + code_name, std::ios::trunc);

       if(!code.is_open()) return;


       coding->setCodeFile(&code);

       //Code header
       coding->codeFileBegin();
       coding->codeAddHeaders();

       this->recursive_code_generation(folder->root(), code,"");

       coding->codeFileEnd();
       //Close file
       code.close();
    }
private:
    void recursive_code_generation(const FileItem* item,std::ofstream& code_file,std::string indent)
    {
        //TODO add indent

        //Get and format class name(from folder name) -> language rules (kind of universal)
        string class_name = naming->getClassNameFromFolder(item);

        coding->codeStructureBegin(class_name, indent);

        std::string next_indent = indent + "    ";
        for(const auto& subitem : item->subFiles())
        {
            if(!naming->checkNameVality(&subitem))
            {
                std::cout << "INCORRECT NAMING OF: " << subitem.name() << " at path: " << subitem.absolutePath() << endl;
                std::cout << "Files or Folders must start in alphabet character" << endl;
                continue;
            }
            if(subitem.isFile())
            {
                std::cout << "Adding File: " << subitem.name() << std::endl;
                //Get and format file name
                std::string item_name = naming->getVarNameFromFile(&subitem);

                //Get and format relative/absolute path
                std::string path_name = naming->getFilePath(&subitem);
                coding->codeAddFile(item_name, path_name, next_indent);
            }
            else if(subitem.isFolder())
            {

                //Repeat
                this->recursive_code_generation(&subitem, code_file,next_indent);
            }
            else
            {
                //DO nothing
            }
        }

        coding->codeStrucutreEnd(class_name, indent);
    }
    std::ofstream code;
    CodeGenerator* coding;
    ResFileName* naming;

};
