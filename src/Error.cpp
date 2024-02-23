//
// Created by Rohith on 1/8/24.
//

#include "Error.h"
#include <iostream>

bool crux::hasError = false;
bool crux::hadRuntimeError = false;

void crux::error(Token &token, std::string_view message) {
    if (token.type == EOF) {
        report(token.line, "at end", message);
    } else {
        report(token.line, "at", message);
    }
}


void crux::report(int line,  std::string_view where, std::string_view message) {
std::cout<<"[line "<<line<<"]"<<"Error "<<": "<<message<<std::endl;
hasError = true;
}

void crux::error(int line, std::string_view message) {
    crux::report(line, "", message);
}

void crux::runtimeError(RuntimeError &error) {
    std::cerr << error.what() <<
    "\n[line " << error.token.line << "]\n";
    hadRuntimeError = true;
}