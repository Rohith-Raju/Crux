//
// Created by Rohith on 1/3/24.
//

#ifndef CRUX_TOKEN_H
#define CRUX_TOKEN_H

#include "utls/Object.h"
#include <string>

enum TokenType {
  // Single-character tokens.
  LEFT_PAREN,
  RIGHT_PAREN,
  LEFT_BRACE,
  RIGHT_BRACE,
  COMMA,
  DOT,
  MINUS,
  PLUS,
  COLON,
  SEMICOLON,
  SLASH,
  STAR,
  QUESTON_MARK,

  // One or two character tokens.
  BANG,
  BANG_EQUAL,
  EQUAL,
  EQUAL_EQUAL,
  GREATER,
  GREATER_EQUAL,
  LESS,
  LESS_EQUAL,

  // Literals.
  IDENTIFIER,
  STRING,
  NUMBER,

  // Keywords.
  AND,
  CLASS,
  ELSE,
  FALSE,
  FUN,
  FOR,
  IF,
  NIL,
  OR,
  PRINT,
  RETURN,
  SUPER,
  THIS,
  TRUE,
  VAR,
  WHILE,
  BREAK,

  ENDOFFILE
};

struct null {};

class Token {
public:
  TokenType type;
  std::string lexeme;
  Object literal;
  int line;

  Token(TokenType type, std::string lexeme, Object literal, int line)
      : type(type), lexeme(lexeme), literal(std::move(literal)), line(line) {}
};

#endif // CRUX_TOKEN_H
