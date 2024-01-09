//
// Created by Rohith on 1/8/24.
//

#include "Error.h"
#include <iostream>

bool hasError = false;

void error(int line, const char *message) {
    report(line, message);
}


void report(int line, const char *message) {
std::cout<<"[line "<<line<<"]"<<"Error "<<": "<<message<<std::endl;
hasError = true;
}