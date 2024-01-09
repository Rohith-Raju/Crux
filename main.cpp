#include "src/Scanner.h"
#include <iostream>

void runCode(std::string source);


void runPromt(){
    for(;;){
        std::cout<<"> ";
        std::string line;
        std::getline(std::cin, line);
        if(std::cin.eof()){
            std::cout<<line;
            break;
        }
        runCode(line);
        if(hasError) exit(1);
    }
}

void runCode(std::string source){
    Scanner scanner(source);
    scanner.scanTokens();
    for(auto tkn : scanner.tokens){
        std::cout<<tkn.type<<std::endl;
    }

}

int main() {
    runPromt();
    return 0;
}
