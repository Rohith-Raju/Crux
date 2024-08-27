//
// Created by Rohith on 18/03/24
//
//
#ifndef CRUX_STATEMENT_H
#define CRUX_STATEMENT_H

#include "Expr.h"
#include "Token.h"
#include <vector>

enum Statement_type {
  StmntExpr_type,
  StmntPrint_type,
  StmntVar_type,
  StmntBlock_type,
  StmntIf_type,
  StmntWhile_type,
  StmntBreak_type,
  StmntFunc_type,
  StmntReturn_type,
  StmntClass_type
};

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

class Block : public Statement {
public:
  std::vector<Statement *> stmnt;
  Block(std::vector<Statement *> stmnt);
};

class If : public Statement {
public:
  Expr *condition;
  Statement *thenBranch;
  Statement *elseBranch;

  If(Expr *expression, Statement *thenBranch, Statement *elseBranch);
  ~If();
};

class While : public Statement {
public:
  Expr *condition;
  Statement *body;
  While(Expr *condition, Statement *body);
  ~While();
};

class Break : public Statement {
public:
  bool isBreakPresent = false;
  Break(bool breakSet);
};

class Function : public Statement {
public:
  Token *name;
  std::vector<Token *> params;
  std::vector<Statement *> body;

  Function(Token *name, std::vector<Token *> params,
           std::vector<Statement *> body);
};

class Return : public Statement {
public:
  Token *keyword;
  Expr *value;
  Return(Token *keyword, Expr *value);
};

class Class : public Statement {
public:
  Token *name;
  std::vector<Function *> methods;
  Class(Token *name, std::vector<Function *> methods);
};

#endif
