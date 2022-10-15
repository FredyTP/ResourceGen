#pragma once

#include "CppCodeGen.h"

class JavaCodeGen : public CppCodeGen
{
private:
    std::string package;
public:
    JavaCodeGen(std::string _package) : CppCodeGen()
    {
        this->package = _package;
    }

    virtual void codeStructureBegin(std::string classname, std::string indent)
    {
        using std::endl;
        std::string indent2 = indent + "    ";
        //code structure begin
        this->addNewLine();
        *code << indent << "public class " + classname << endl;
        *code << indent << "{" << endl;
        *code << indent2 <<"private "+ classname + "(){}" << endl;
    }
    virtual void codeStrucutreEnd(std::string classname, std::string indent)
    {
        *code << indent << "}" << std::endl;
        this->addNewLine();
    }
    virtual void codeAddFile(std::string varname, std::string path, std::string indent)
    {
        using std::endl;
        *code << indent << "public static String " + varname + " = " + this->makeCodeString(path) + ";" << endl;
    }
    virtual void codeAddHeaders()
    {
        using std::endl;
        *code << "package " + package + ";";
    }
protected:
};

class JavaFileName : public CppFileName
{
public:
    JavaFileName(bool _absolute = false) : CppFileName(_absolute)
    {

    }

    /**
    * Replace all "." and " " with "_".
    *
    * \param folder
    * \return
    */
    virtual std::string getClassNameFromFolder(const FileItem* folder)
    {
        std::string classname = ResFileName::getClassNameFromFolder(folder);
        classname.at(0) = toupper(classname.at(0));
        return classname;

    };
    virtual std::string getCodeFileName(const FileTree* folder)
    {
        string code_name = this->getClassNameFromFolder(folder->root()) + ".java";
        return code_name;
    }
};
