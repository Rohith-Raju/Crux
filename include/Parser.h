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
  // loopCounter to determine if "break" is valid or not. (break should only
  // occur in loops)
  int loopCounter = 0;

  // Precidence
  Expr *Or();
  Expr *And();
  Expr *assignment();
  Expr *expression();
  Expr *ternary();
  Expr *comparison();
  Expr *term();
  Expr *factor();
  Expr *unary();
  Expr *call();
  Expr *primary();

  // Expr helper functions
  Expr *finishCall(Expr *expr);

  // Statement helper functions
  Statement *statement();
  Statement *printStatement();
  Statement *ifStatement();
  Statement *whileStatement();
  Statement *forStatement();
  Statement *breakStatement();
  Statement *expressionStatement();
  Statement *function(std::string str);
  Statement *returnStatement();
  std::vector<Statement *> blockStatement();

  // Variable stuff
  Statement *declaration();
  Statement *varDeclaration();

  // Helper functions
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
