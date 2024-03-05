//
// Created by Rohith on 2/9/24.
//

#ifndef CRUX_PARSER_H
#define CRUX_PARSER_H

#include "Error.h"
#include "Expr.h"
#include "Token.h"
#include <cassert>
#include <memory>
#include <utility> //std::move()
#include <vector>

class Parser {
private:
  struct ParseError : public std::runtime_error {
    using std::runtime_error::runtime_error;
  };
  std::vector<Token> tokens;
  int current = 0;
  Expr *expression();
  Expr *comparison();
  Expr *term();
  Expr *factor();
  Expr *unary();
  Expr *primary();

  // helper functions
  Expr *equality();
  bool check(TokenType type);
  Token advance();
  bool isAtEnd();
  Token peek();
  Token previous();
  Token consume(TokenType type, std::string message);
  template <class... T> bool match(T... type);
  ParseError error(Token token, std::string message);
  void synchronize();

public:
  Parser(const std::vector<Token> &tokens) : tokens{tokens} {};
  Expr *parse();
};

#endif // CRUX_PARSER_H
