//
// Resolver.cpp
//

#include "Resolver.h"
#include "Error.h"
#include "Expr.h"
#include "Statement.h"
#include "Token.h"
#include <string>
#include <unordered_map>
#include <vector>

Resolver::Resolver(Interpreter *interpreter) : interpreter(interpreter) {}

void Resolver::resolve(std::vector<Statement *> stmnts) {
  for (Statement *stmnt : stmnts) {
    resolve(stmnt);
  }
}

void Resolver::resolve(Statement *stmnt) {
  switch (stmnt->type) {
  case StmntPrint_type:
    visitPrintStmnt((Print *)stmnt);
    break;
  case StmntExpr_type:
    visitExprStmnt((Expression *)stmnt);
    break;
  case StmntVar_type:
    visitVarStmnt((Var *)stmnt);
    break;
  case StmntBlock_type:
    visitBlockStmnt((Block *)stmnt);
    break;
  case StmntIf_type:
    visitIfStmnt((If *)stmnt);
    break;
  case StmntWhile_type:
    visitWhileStmnt((While *)stmnt);
    break;
  case StmntFunc_type:
    visitFuncStmnt((Function *)stmnt);
    break;
  case StmntReturn_type:
    visitReturnStmnt((Return *)stmnt);
    break;
  case StmntBreak_type:
    break;
  }
}

void Resolver::resolve(Expr *expr) {
  switch (expr->type) {
  case ExprType_Binary:
    return visitBinaryExp((Binary *)expr);
  case ExprType_Unary:
    return visitUnaryExp((Unary *)expr);
  case ExprType_Literal:
    return visitLiteral((Literal *)expr);
  case ExprType_Grouping:
    return visitGroupExp((Grouping *)expr);
  case ExprType_Ternary:
    return visitTernaryExp((Ternary *)expr);
  case ExprType_Variable:
    return visitVariableExp((Variable *)expr);
  case ExprType_Assignment:
    return visitAssignment((Assignment *)expr);
  case ExprType_Logical:
    return visitLogicalExp((Logical *)expr);
  case ExprType_Call:
    return visitCall((Call *)expr);
  }
}

void Resolver::beginScope() {
  scopes.push_back(new std::unordered_map<std::string, varFlags>());
}

void Resolver::endScope() {
  auto scope = scopes.back();
  delete scope;
  scopes.pop_back();
}

void Resolver::declare(Token *name) {
  if (scopes.empty())
    return;
  std::unordered_map<std::string, varFlags> *scope = scopes.back();

  if (scope->find(name->lexeme) != scope->end())
    crux::error(*name, "Variable already declared with the same name");

  (*scope)[name->lexeme].isReferenced = false;
  (*scope)[name->lexeme].isInitilized = false;
}

void Resolver::define(Token *name) {
  if (scopes.empty())
    return;
  std::unordered_map<std::string, varFlags> *scope = scopes.back();
  (*scope)[name->lexeme].isInitilized = true;
}

void Resolver::resolveLocal(Expr *expr, Token *name) {
  for (int i = scopes.size() - 1; i >= 0; i--) {
    if (scopes[i]->find(name->lexeme) != scopes[i]->end()) {
      interpreter->resolve(expr, scopes.size() - i - 1);
      return;
    }
  }
}

void Resolver::visitBlockStmnt(Block *block) {
  beginScope();
  resolve(block->stmnt);
  endScope();
}

void Resolver::visitVarStmnt(Var *stmnt) {
  declare(stmnt->name);
  if (stmnt->expression != nullptr) {
    resolve(stmnt->expression);
  }
  define(stmnt->name);
}

void Resolver::visitVariableExp(Variable *expr) {
  if (!scopes.empty()) {
    auto scope = scopes.back();
    auto it = scope->find(expr->name->lexeme);
    if (it != scope->end() && !it->second.isInitilized == true)
      crux::error(*expr->name,
                  "Can't read local variable in its own initializer.");
  }
  resolveLocal(expr, expr->name);
}

void Resolver::visitAssignment(Assignment *expr) {
  resolve(expr->value);
  resolveLocal(expr, expr->name);
}

void Resolver::visitFuncStmnt(Function *stmnt) {
  declare(stmnt->name);
  define(stmnt->name);
  resolveFunction(stmnt, FunctionType_Function);
}

void Resolver::resolveFunction(Function *stmnt, FunctionType type) {
  FunctionType enclosingFunction = currentFunction;
  currentFunction = type;
  beginScope();
  for (Token *params : stmnt->params) {
    declare(params);
    define(params);
  }
  resolve(stmnt->body);
  endScope();
  currentFunction = enclosingFunction;
}

void Resolver::visitExprStmnt(Expression *stmnt) { resolve(stmnt->expression); }

void Resolver::visitIfStmnt(If *stmnt) {
  resolve(stmnt->condition);
  resolve(stmnt->thenBranch);
  if (stmnt->elseBranch)
    resolve(stmnt->elseBranch);
}

void Resolver::visitPrintStmnt(Print *expr) { resolve(expr->expression); }

void Resolver::visitReturnStmnt(Return *expr) {
  if (currentFunction == FunctionType_None) {
    crux::error(*expr->keyword, "Can't return from top level");
  }
  if (expr->value)
    resolve(expr->value);
}

void Resolver::visitWhileStmnt(While *stmnt) {
  resolve(stmnt->condition);
  resolve(stmnt->body);
}

void Resolver::visitBinaryExp(Binary *expr) {
  resolve(expr->left);
  resolve(expr->right);
}

void Resolver::visitCall(Call *expr) {
  resolve(expr->callee);
  for (Expr *arg : expr->arguments)
    resolve(arg);
}

void Resolver::visitGroupExp(Grouping *expr) { resolve(expr->expression); }

void Resolver::visitLiteral(Literal *expr) { return; }

void Resolver::visitLogicalExp(Logical *expr) {
  resolve(expr->left);
  resolve(expr->right);
}

void Resolver::visitUnaryExp(Unary *expr) { resolve(expr->right); }

void Resolver::visitTernaryExp(Ternary *expr) {
  resolve(expr->condition);
  resolve(expr->expression1);
  resolve(expr->expression2);
}
