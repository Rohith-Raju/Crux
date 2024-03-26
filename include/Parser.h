//

#ifndef CRUX_PARSER_H
#define CRUX_PARSER_H

#include "Expr.h"
#include "Token.h"
#include <Statement.h>
#include <stdexcept>
#include <vector>

class Parser {
private:
  struct ParseError : public std::runtime_error {
    using std::runtime_error::runtime_error;
  };
  std::vector<Token> tokens;
  int current = 0;
  Expr *expression();
  Expr *ternary();
  Expr *comparison();
  Expr *term();
  Expr *factor();
  Expr *unary();
  Expr *primary();

  // Statement helper functions
  Statement *statement();
  Statement *printStatement();
  Statement *expressionStatement();

  // Variable stuff
  Statement *declaration();
  Statement *varDeclaration();

  // helper functions
  Expr *equality();
  bool check(TokenType type);
  Token advance();
  bool isAtEnd();
  Token peek();
  Token peek_next();
  Token previous();
  Token consume(TokenType type, std::string message);
  template <class... T> bool match(T... type);
  ParseError error(Token token, std::string message);
  void synchronize();

public:
  Parser(const std::vector<Token> &tokens) : tokens{tokens} {};
  std::vector<Statement *> parse();
};

#endif // CRUX_PARSER_H
