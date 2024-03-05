//
// Created by Rohith on 1/25/24.
//

#ifndef CRUX_EXPR_H
#define CRUX_EXPR_H

#include "Token.h"

enum ExprType {
  ExprType_Binary,
  ExprType_Grouping,
  ExprType_Unary,
  ExprType_Literal
};

class Expr {
public:
  ExprType type;

  Expr(ExprType type);

  virtual ~Expr();
};

class Binary : public Expr {
public:
  Expr *left;
  Token *op;
  Expr *right;

  Binary(Expr *left, Token *op, Expr *right);

  ~Binary();
};

class Grouping : public Expr {
public:
  Expr *expression;

  Grouping(Expr *expression);

  ~Grouping();
};

class Unary : public Expr {
public:
  Token *op;
  Expr *right;

  Unary(Token *op, Expr *right);

  ~Unary();
};

class Literal : public Expr {
public:
  Object *literal;

  Literal(Object *literal);

  ~Literal();
};

#endif
