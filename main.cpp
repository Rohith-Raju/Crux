#include "Scanner.h"
#include <iostream>
#include <Parser.h>
#include "PrettyPrinter.h"
#include "Interpreter.h"

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
        if(crux::hasError) exit(1);
        if(crux::hadRuntimeError) exit(1);
    }
}

void runCode(std::string source){
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.scanTokens();
    Parser parser(tokens);
    std::shared_ptr<Expr> expression = parser.parse();
    std::unique_ptr<Interpreter> interpreter = std::make_unique<Interpreter>();
    interpreter->interpret(expression);
}

int main() {
    runPromt();
    return 0;
}
