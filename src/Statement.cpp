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

Block::Block() : Statement(StmntBlock_type) {}

Block::Block(std::vector<Statement *> stmnt)
    : Statement(StmntBlock_type), stmnt(stmnt) {}
