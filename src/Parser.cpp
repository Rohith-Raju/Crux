//
// Created by Rohith on 2/9/24.
//
#include "Parser.h"
#include "Expr.h"
#include "Token.h"

Expr *Parser::parse() {
  try {
    return expression();
  } catch (ParseError error) {
    return nullptr;
  }
}

Expr *Parser::expression() { return equality(); }

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

  if (match(NUMBER, STRING)) {
    return new Literal(new Object(previous().literal));
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
  assert((... && std::is_same_v<T, TokenType>));
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
