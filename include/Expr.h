//

#ifndef CRUX_EXPR_H
#define CRUX_EXPR_H

#include "Token.h"
#include <vector>

enum ExprType {
  ExprType_Binary,
  ExprType_Grouping,
  ExprType_Unary,
  ExprType_Literal,
  ExprType_Ternary,
  ExprType_Variable,
  ExprType_Assignment,
  ExprType_Logical,
  ExprType_Call
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

class Call : public Expr {
public:
  Expr *callee;
  Token *paren;
  std::vector<Expr *> arguments;

  Call(Expr *callee, Token *paren, std::vector<Expr *> arguments);

  ~Call();
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

class Ternary : public Expr {
public:
  Expr *condition;
  Token *op1;
  Expr *expression1;
  Token *op2;
  Expr *expression2;

  Ternary(Expr *condt, Token *op1, Expr *expr1, Token *op2, Expr *expr2);

  ~Ternary();
};

class Logical : public Expr {
public:
  Expr *left;
  Token *op;
  Expr *right;
  Logical(Expr *left, Token *op, Expr *right);

  ~Logical();
};

class Literal : public Expr {
public:
  Object *literal;

  Literal(Object *literal);

  ~Literal();
};

class Variable : public Expr {
public:
  Token *name;

  Variable(Token *name);

  ~Variable();
};

class Assignment : public Expr {
public:
  Token *name;

  Expr *value;

  Assignment(Token *name, Expr *value);

  ~Assignment();
};

#endif
