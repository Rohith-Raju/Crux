//
// Created by Rohith on 18/03/24
//
//
#ifndef CRUX_STATEMENT_H
#define CRUX_STATEMENT_H

#include "Expr.h"

enum Statement_type { StmntExpr_type, StmntPrint_type, StmntVar_type };

class Statement {
public:
  Statement_type type;
  Statement(Statement_type type);
};

class Print : public Statement {
public:
  Expr *expression;
  Print(Expr *expression);
  ~Print();
};

class Expression : public Statement {
public:
  Expr *expression;
  Expression(Expr *expression);
  ~Expression();
};

class Var : public Statement {
public:
  Token *name;
  Expr *expression;
  Var(Token *name, Expr *expression);
  ~Var();
};

#endif
