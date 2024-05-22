
#ifndef CRUX_RESOLVER_H
#define CRUX_RESOLVER_H

#include "Interpreter.h"
#include <stack>
#include <unordered_map>
#include <vector>

struct varFlags {
  bool isInitilised;
  bool isReferenced;
};

class Resolver {

private:
  std::vector<std::unordered_map<std::string, varFlags> *> scopes;
  Interpreter *interpreter;
  Resolver(Interpreter *interpreter);

public:
  void resolve(std::vector<Statement *> stmnts);
  void resolve(Expr *expr);
  void resolve(Statement *stmnt);

  void beginScope();
  void endScope();

  void declare(Token *name);
  void define(Token *name);

  void resolveLocal(Expr *expr, Token *name);

  Object excecuteBlock(std::vector<Statement *> stmnts, Environment *env);

  void interpret(std::vector<Statement *> &statements);

  void visitPrintStmnt(Print *stmnt);

  void visitBlockStmnt(Block *stmnt);

  void visitExprStmnt(Expression *stmnt);

  void visitVarStmnt(Var *stmnt);

  void visitIfStmnt(If *stmnt);

  void visitWhileStmnt(While *stmnt);

  void visitFuncStmnt(Function *stmnt);

  void visitReturnStmnt(Return *stmnt);

  void visitAssignment(Assignment *expr);

  void visitLogicalExp(Logical *expr);

  void visitLiteral(Literal *expr);

  void visitGroupExp(Grouping *expr);

  void visitCall(Call *stmnt);

  void visitUnaryExp(Unary *expr);

  void visitBinaryExp(Binary *expr);

  void visitTernaryExp(Ternary *expr);

  void visitVariableExp(Variable *expr);
};

#endif // CRUX_RESOLVER_H
