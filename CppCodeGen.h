#pragma once

#include "ResCodeGenerator.h"

class CppCodeGen : public CodeGenerator
{
public:
    virtual void codeStructureBegin(std::string classname, std::string indent)
    {
        using std::endl;
        std::string indent2 = indent + "    ";
        //code structure begin
        this->addNewLine();
        *code << indent << "class " + classname << endl;    
        *code << indent << "{" << endl;                     
        *code << indent << "private:" << endl;              
        *code << indent2 << classname + "(){}" << endl;      
        *code << indent << "public:" << endl;               
    }
    virtual void codeStrucutreEnd(std::string classname, std::string indent)
    {
        *code << indent <<"};" << std::endl;
        this->addNewLine();
    }
    virtual void codeAddFile(std::string varname, std::string path, std::string indent)
    {
        using std::endl;
        *code << indent << "inline static const std::string " + varname + " = " + this->makeCodeString(path) + ";" << endl;
    }
    virtual void codeAddHeaders()
    {
        using std::endl;
        *code << "#pragma once" << endl;
        *code << "#include <string>" << endl;
    }
protected:

};

class CppFileName : public ResFileName
{
public:
    CppFileName(bool _absolute = false) : ResFileName(_absolute)
    {

    }
};
