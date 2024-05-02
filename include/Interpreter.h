//
// Created by Rohith on 2/17/24.
//

#ifndef CRUX_INTERPRETER_H
#define CRUX_INTERPRETER_H

#include "Expr.h"
#include "Statement.h"
#include "Token.h"
#include "env/Env.h"
#include "utls/Object.h"
#include <vector>

class Interpreter {
private:
  static Environment *environment;

  void excecute(Statement *stmnt);

  Object evaluate(Expr *expr);

  bool isTruthy(Object right);

  bool isEqual(Object left, Object right);

  void checkNumberOperand(Token *op, Object right);

  bool checkIfSameTypes(Object left, Object right);

  bool checkCompatibility(Token *op, Object left, Object right);

public:
  static Environment *globals;

  Interpreter();

  bool isBreakUsed = false;

  void excecuteBlock(std::vector<Statement *> stmnts, Environment *env);

  void interpret(std::vector<Statement *> &statements);

  void visitPrintStmnt(Print *stmnt);

  void visitBlockStmnt(Block *stmnt);

  Object visitExprStmnt(Expression *stmnt);

  void visitVarStmnt(Var *stmnt);

  void visitIfStmnt(If *stmnt);

  void visitWhileStmnt(While *stmnt);

  void visitFuncStmnt(Function *stmnt);

  Object visitAssignment(Assignment *expr);

  Object visitLogicalExp(Logical *expr);

  Object visitLiteral(Literal *expr);

  Object visitGroupExp(Grouping *expr);

  Object visitCall(Call *stmnt);

  Object visitUnaryExp(Unary *expr);

  Object visitBinaryExp(Binary *expr);

  Object visitTernaryExp(Ternary *expr);

  Object visitVariableExp(Variable *expr);
};

#endif // CRUX_INTERPRETER_H
