#include "Interpreter.h"
#include "PrettyPrinter.h"
#include "Scanner.h"
#include <Parser.h>
#include <iostream>

void runCode(std::string source);

void runPromt() {
  for (;;) {
    std::cout << "> ";
    std::string line;
    std::getline(std::cin, line);
    if (std::cin.eof()) {
      std::cout << line;
      break;
    }
    runCode(line);
    if (crux::hasError)
      exit(1);
    if (crux::hadRuntimeError)
      exit(1);
  }
}

void runCode(std::string source) {
  Scanner scanner(source);
  std::vector<Token> tokens = scanner.scanTokens();
  Parser parser(tokens);
  Expr *expression = parser.parse();
  std::unique_ptr<Interpreter> interpreter = std::make_unique<Interpreter>();
  interpreter->interpret(expression);
}

int main() {
  runPromt();
  return 0;
}
