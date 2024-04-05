// Object
#include "Parser.h"
#include "Error.h"
#include "Expr.h"
#include "Statement.h"
#include "Token.h"
#include <vector>

std::vector<Statement *> Parser::parse() {
  std::vector<Statement *> statements;
  while (!isAtEnd()) {
    Statement *stmt = declaration();
    if (crux::hasError) {
      synchronize();
      if (stmt) {
        delete stmt;
      }
      stmt = nullptr;
      break;
    } else {
      statements.push_back(stmt);
    }
  }
  return statements;
}

Statement *Parser::declaration() {
  if (match(VAR))
    return varDeclaration();
  return statement();
}

Statement *Parser::varDeclaration() {
  Token *name = new Token(consume(IDENTIFIER, "variable name required"));

  Expr *initializer = nullptr;

  if (match(EQUAL)) {
    initializer = expression();
  }

  consume(SEMICOLON, "Expected ; after the variable declaration");
  return new Var(name, initializer);
}

Statement *Parser::statement() {
  if (match(PRINT))
    return printStatement();
  if (match(LEFT_BRACE))
    return new Block(blockStatement());
  return expressionStatement();
}

std::vector<Statement *> Parser::blockStatement() {
  std::vector<Statement *> stmnts;

  if (!check(RIGHT_BRACE) && !isAtEnd()) {
    stmnts.push_back(declaration());
  }

  consume(RIGHT_BRACE, "Expect closing } after the block");
  return stmnts;
}

Statement *Parser::printStatement() {
  Expr *expr = expression();
  consume(SEMICOLON, "Expected ; at the end of the statement");
  return new Print(expr);
}

Statement *Parser::expressionStatement() {
  Expr *expr = expression();
  consume(SEMICOLON, "Expected ; at the end of the statement");
  return new Expression(expr);
}

Expr *Parser::expression() { return assignment(); }

Expr *Parser::assignment() {
  Expr *expr = ternary();

  if (match(EQUAL)) {
    Token equals = previous();
    Expr *value = assignment();
    if (expr->type == ExprType_Variable) {
      Variable *var = (Variable *)expr;
      Token *name = var->name;
      return new Assignment(name, value);
    }
    error(equals, "Invalid assignment target.");
  }
  return expr;
}

Expr *Parser::ternary() {
  Expr *expr = equality();
  if (match(QUESTON_MARK)) {
    Token *questionMark = new Token(previous());
    Expr *expr1 = equality();
    if (match(COLON)) {
      Token *colon = new Token(previous());
      Expr *expr2 = equality();
      expr = new Ternary(expr, questionMark, expr1, colon, expr2);
    } else {
      error(peek(), "Expected:");
      delete questionMark;
      delete expr1;
    }
  }
  return expr;
}

Expr *Parser::equality() {
  Expr *expr = comparison();
  while (match(EQUAL_EQUAL, BANG_EQUAL)) {
    Token *op = new Token(previous());
    Expr *right = comparison();
    expr = new Binary(expr, op, right);
  }
  return expr;
}

Expr *Parser::comparison() {
  Expr *expr = term();
  while (match(GREATER, GREATER_EQUAL, LESS_EQUAL, LESS)) {
    Token *op = new Token(previous());
    Expr *right = term();
    expr = new Binary(expr, op, right);
  }
  return expr;
}

Expr *Parser::term() {
  Expr *expr = factor();
  while (match(MINUS, PLUS)) {
    Token *op = new Token(previous());
    Expr *right = factor();
    expr = new Binary(expr, op, right);
  }
  return expr;
}

Expr *Parser::factor() {
  Expr *expr = unary();
  while (match(SLASH, STAR)) {
    Token *op = new Token(previous());
    Expr *right = unary();
    expr = new Binary(expr, op, right);
  }
  return expr;
}

Expr *Parser::unary() {
  while (match(BANG, MINUS)) {
    Token *op = new Token(previous());
    Expr *right = primary();
    return new Unary(op, right);
  }
  return primary();
}

Expr *Parser::primary() {
  if (match(FALSE))
    return new Literal(new Object(false));

  if (match(TRUE))
    return new Literal(new Object(true));

  if (match(NIL))
    return new Literal(new Object());

  if (match(NUMBER)) {
    return new Literal(new Object(previous().literal));
  }

  if (match(STRING)) {
    return new Literal(new Object(previous().literal));
  }

  if (match(IDENTIFIER)) {
    return new Variable(new Token(previous()));
  }

  if (match(LEFT_PAREN)) {
    Expr *expr = expression();
    consume(RIGHT_PAREN, "Expect ')' after expression.");
    return new Grouping(expr);
  }
  throw error(peek(), "Expect expression.");
}

Token Parser::consume(TokenType type, std::string message) {
  if (check(type))
    return advance();

  throw error(peek(), message);
}

template <class... T> bool Parser::match(T... type) {
  if ((... || check(type))) {
    advance();
    return true;
  }
  return false;
}

bool Parser::check(TokenType type) {
  if (isAtEnd())
    return false;
  return peek().type == type;
}

Token Parser::advance() {
  if (!isAtEnd())
    ++current;
  return previous();
}

Token Parser::previous() { return tokens[current - 1]; }

Token Parser::peek() { return tokens[current]; }

Token Parser::peek_next() { return tokens[current + 1]; }

bool Parser::isAtEnd() { return peek().type == ENDOFFILE; }

typename Parser::ParseError Parser::error(Token token, std::string message) {
  crux::error(token, message);
  return ParseError("");
}

void Parser::synchronize() {
  advance();

  while (!isAtEnd()) {
    if (previous().type == SEMICOLON)
      return;
    switch (peek().type) {
    case CLASS:
    case FUN:
    case VAR:
    case FOR:
    case IF:
    case WHILE:
    case PRINT:
    case RETURN:
      return;
    }
    advance();
  }
}
