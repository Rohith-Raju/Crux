#include "Error.h"
#include "Interpreter.h"
#include "Resolver.h"
#include "Scanner.h"
#include <Parser.h>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

void runCode(std::string source);

std::string readFile(fs::path path) {
  if (path.extension() != ".crux") {
    std::cerr << "Filename " << path.filename()
              << " should end with the extension \".crux\" \n";
    exit(64);
  }

  std::ostringstream data;
  std::fstream file(path, std::ios_base::in);
  if (!file.is_open()) {
    std::cerr << "File could't be found or opened \n";
    exit(64);
  }
  data << file.rdbuf();
  return data.str();
}

void runFile(std::string path) {
  fs::path fPath(path);
  runCode(readFile(fPath));
}

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

Interpreter interpreter{};

void runCode(std::string source) {
  Scanner scanner(source);
  std::vector<Token> tokens = scanner.scanTokens();
  Parser parser(tokens);
  std::vector<Statement *> statements = parser.parse();
  Resolver *resolver = new Resolver(&interpreter);
  resolver->resolve(statements);
  if (crux::hadRuntimeError)
    return;
  interpreter.interpret(statements);
}

int main(int argc, char *argv[]) {
  if (argc > 2) {
    std::cout << "usage: crux <script>\n";
    std::cout << "using repl: ./crux\n";
    exit(64);
  } else if (argc == 2) {
    runFile(argv[1]);
  } else {
    runPromt();
  }
  return 0;
}
