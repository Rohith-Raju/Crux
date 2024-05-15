//
// Created by Rohith in 18/03/24
//

#include "Statement.h"
#include <vector>

Statement::Statement(Statement_type type) : type(type) {}

Print::Print(Expr *expr) : Statement(StmntPrint_type), expression(expr) {}
Print::~Print() { delete expression; }

Expression::Expression(Expr *expr)
    : Statement(StmntExpr_type), expression(expr) {}

Expression::~Expression() { delete expression; }

Var::Var(Token *name, Expr *expression)
    : Statement(StmntVar_type), name(name), expression(expression) {}

Var::~Var() {
  delete name;
  delete expression;
}

Block::Block(std::vector<Statement *> stmnt)
    : Statement(StmntBlock_type), stmnt(stmnt) {}

If::If(Expr *condition, Statement *thenBranch, Statement *elseBranch)
    : Statement(StmntIf_type), condition(condition), thenBranch(thenBranch),
      elseBranch(elseBranch) {}

If::~If() {
  delete condition;
  delete thenBranch;
  delete elseBranch;
}

While::While(Expr *condition, Statement *body)
    : Statement(StmntWhile_type), condition(condition), body(body) {}

While::~While() {
  delete condition;
  delete body;
}

Break::Break(bool isBrkPre)
    : Statement(StmntBreak_type), isBreakPresent(isBrkPre) {}

Function::Function(Token *name, std::vector<Token *> params,
                   std::vector<Statement *> body)
    : Statement(StmntFunc_type), name(name), params(params), body(body) {}

Return::Return(Token *keyword, Expr *value)
    : Statement(StmntReturn_type), keyword(keyword), value(value) {}
