//
// Created by Rohith on 1/17/24.
//
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>


void trimString(std::string &str) {
    str.erase(0, str.find_first_not_of(" "));
    str.erase(str.find_last_not_of(" ") + 1);
}

void defineType(std::ofstream &writer, std::string basename, std::string &className, std::string &fields)
{
    if (!basename.empty())
    {
        writer << "class " << className << " : public " << basename << std::endl;
    }
    else
    {
        writer << "class " << className << std::endl;
    }
    writer << "{" << std::endl;
    writer << "    // " << fields << std::endl;
    writer << "};" << std::endl << std::endl;
}

void defineAst (std::string outdir, std::string baseClass, std::vector<std::string>&data){
    std::ofstream writerH{outdir+baseClass + ".h"};

    //error check
    if(writerH.bad()){
        std::cerr<<"failed to create/open .h file";
        std::exit(64);
    }

    writerH << "#pragma once"<< "\n" <<"\n";

    //includes
    writerH << "#include \"Token.h\"" <<"\n"<<"\n";

    std::string baseClassName(baseClass);
    std::string baseFields;
    defineType(writerH, "", baseClassName, baseFields);

    for (auto &type : data) {
        std::stringstream strStream(type);
        std::string className, field;
        std::getline(strStream,className,':');
        std::getline(strStream,field,':');
        trimString(className);
        trimString(field);
        defineType(writerH,baseClass,className,field);
    }

    writerH.close();
}



int main(){
    std::string dir = "../src/";
    std::vector<std::string> expr = {
            "Binary   : Expr left, Token operator, Expr right",
            "Grouping : Expr expression",
            "Literal  : Object value",
            "Unary    : Token operator, Expr right"
    };
    defineAst(dir,"Expr",expr);
}