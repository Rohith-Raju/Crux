//

#include "Interpreter.h"
#include "CruxCallable.h"
#include "CruxClass.h"
#include "CruxInstance.h"
#include "Error.h"
#include "Expr.h"
#include "Function.h"
#include "NativeFunction.h"
#include "Statement.h"
#include "Token.h"
#include "env/Env.h"
#include "utls/Object.h"
#include "utls/RuntimeError.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

Interpreter::Interpreter() {
  if (!environment) {
    globals = new Environment();
    environment = globals;
    Object clock(new ClockFunction());
    globals->define("clock", clock);
  }
}

void Interpreter::excecute(Statement *stmnt) {
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
  case StmntClass_type:
    visitClassStmnt((Class *)stmnt);
    break;
  case StmntBreak_type:
    isBreakUsed = true;
    break;
  }
}

void Interpreter::resolve(Expr *expr, int depth) { locals[expr] = depth; }

Object Interpreter::evaluate(Expr *expr) {
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
  return Object();
}

bool Interpreter::isTruthy(Object right) {
  if (right.type == nullptr_type)
    return false;
  if (right.type == bool_type)
    return right.bool_literal;
  return true;
}

bool Interpreter::isEqual(Object left, Object right) {
  if (left.type == nullptr_type && right.type == nullptr_type)
    return true;
  if (left.type == nullptr_type)
    return false;

  return left.num_literal == right.num_literal;
}

void Interpreter::checkNumberOperand(Token *op, Object right) {
  if (right.type == num_type)
    return;
  RuntimeError(*op, "Operand must be a number");
}

bool Interpreter::checkIfSameTypes(Object left, Object right) {
  if (left.type == right.type)
    return true;
  else
    return false;
}

bool Interpreter::checkCompatibility(Token *op, Object left, Object right) {
  if ((left.type == string_type && right.type == num_type) ||
      left.type == num_type && right.type == string_type) {
    return true;
  } else {
    return false;
  }
}

void Interpreter::interpret(std::vector<Statement *> &statements) {
  try {
    for (auto &stmt : statements) {
      if (stmt)
        excecute(stmt);
    }
  } catch (RuntimeError error) {
    crux::runtimeError(error);
  }
}

void Interpreter::visitPrintStmnt(Print *stmnt) {
  Object value = evaluate(stmnt->expression);
  std::cout << value.str() << "\n";
  return;
}

Object Interpreter::visitExprStmnt(Expression *stmnt) {
  Object value = evaluate(stmnt->expression);
  return value;
}

void Interpreter::visitVarStmnt(Var *stmnt) {
  Object value;

  if (stmnt->expression != nullptr) {
    value = evaluate(stmnt->expression);
  }
  environment->define(stmnt->name->lexeme, value);
}

void Interpreter::visitIfStmnt(If *stmnt) {
  if (isTruthy(evaluate(stmnt->condition)))
    excecute(stmnt->thenBranch);
  else if (stmnt->elseBranch)
    excecute(stmnt->elseBranch);
}

void Interpreter::visitWhileStmnt(While *stmnt) {
  while (isTruthy(evaluate(stmnt->condition))) {
    excecute(stmnt->body);
    if (isBreakUsed)
      break;
  }
}

void Interpreter::visitFuncStmnt(Function *stmnt) {
  Object declaration(new CruxFunction(stmnt, environment));
  environment->define(stmnt->name, declaration);
}

void Interpreter::visitReturnStmnt(Return *stmnt) {
  returnObj = evaluate(stmnt->value);
  isReturnUsed = true;
}

void Interpreter::visitBlockStmnt(Block *stmnt) {
  Environment vars(environment);
  excecuteBlock(stmnt->stmnt, &vars);
}

Object Interpreter::excecuteBlock(std::vector<Statement *> stmnts,
                                  Environment *env) {
  Environment *previous = environment;
  environment = env;
  for (Statement *stmnt : stmnts) {
    excecute(stmnt);
    if (isBreakUsed || isReturnUsed || crux::hadRuntimeError)
      break;
  }
  environment = previous;

  if (isReturnUsed) {
    isReturnUsed = false;
    return this->returnObj;
  }

  return Object();
}

Object Interpreter::visitVariableExp(Variable *expr) {
  return lookUpVariable(expr->name, expr);
}

Object Interpreter::lookUpVariable(Token *name, Expr *expr) {
  auto it = locals.find(expr);
  if (it != locals.end())
    return environment->getAt(it->second, name->lexeme);
  else
    return globals->get(name);
}

Object Interpreter::visitLogicalExp(Logical *expr) {
  Object left = evaluate(expr->left);

  if (expr->op->type == OR)
    return isTruthy(left) ? left : Object();
  if (expr->op->type == AND)
    return !isTruthy(left) ? left : Object();

  return evaluate(expr->right);
}

Object Interpreter::visitAssignment(Assignment *expr) {
  Object value = evaluate(expr->value);

  auto it = locals.find(expr);

  if (it != locals.end())
    environment->assignAt(it->second, expr->name, value);
  else
    globals->assign(expr->name, value);

  return value;
}

Object Interpreter::visitLiteral(Literal *expr) { return *expr->literal; }

Object Interpreter::visitGroupExp(Grouping *expr) {
  return evaluate(expr->expression);
}

Object Interpreter::visitCall(Call *stmnt) {
  Object callee = evaluate(stmnt->callee);

  std::vector<Object> arguments;

  for (auto args : stmnt->arguments) {
    arguments.push_back(evaluate(args));
  }

  if (callee.type != function_type && callee.type != class_type) {
    throw RuntimeError(*stmnt->paren, "call only allowed on functions");
  }

  CruxCallable *callable =
      callee.type == function_type ? callee.function : callee.klass;

  if (arguments.size() != callable->arity()) {
    std::stringstream ss;
    ss << "Expected " << callable->arity() << " arguments but got "
       << arguments.size();
    RuntimeError(*stmnt->paren, ss.str());
  }

  return callable->call(this, arguments);
}

Object Interpreter::visitUnaryExp(Unary *expr) {
  Object right = evaluate(expr->right);
  switch (expr->op->type) {
  case BANG:
    return !isTruthy(right);
  case MINUS:
    checkNumberOperand(expr->op, right);
    return -right.num_literal;
  default:
    throw RuntimeError(*expr->op, "Invalid operator used");
  }
  return Object();
}

Object Interpreter::visitBinaryExp(Binary *expr) {
  Object left = evaluate(expr->left);
  Object right = evaluate(expr->right);
  Token *op = expr->op;
  switch (op->type) {
  case MINUS:
    checkIfSameTypes(left, right);
    return left.num_literal - right.num_literal;
  case SLASH:
    checkIfSameTypes(left, right);
    return left.num_literal / right.num_literal;
  case STAR:
    checkIfSameTypes(left, right);
    return left.num_literal * right.num_literal;
  case PLUS:
    if (checkIfSameTypes(left, right)) {
      if (left.type == num_type && right.type == num_type)
        return left.num_literal + right.num_literal;
      if (left.type == string_type && right.type == string_type)
        return left.string_literal + right.string_literal;
    } else if (checkCompatibility(op, left, right)) {
      if (left.type == string_type && right.type == num_type)
        return left.string_literal + std::to_string(right.num_literal);
      else if (left.type == num_type && right.type == string_type)
        return std::to_string(left.num_literal) + right.string_literal;
    }
    throw new RuntimeError(*op, "Error: Cannot evaluate expression");
  case GREATER:
    checkIfSameTypes(left, right);
    return left.num_literal > right.num_literal;
  case GREATER_EQUAL:
    checkIfSameTypes(left, right);
    return left.num_literal >= right.num_literal;
  case LESS:
    checkIfSameTypes(left, right);
    return left.num_literal < right.num_literal;
  case LESS_EQUAL:
    checkIfSameTypes(left, right);
    return left.num_literal <= right.num_literal;
  case BANG_EQUAL:
    return !isEqual(left, right);
  case EQUAL_EQUAL:
    return isEqual(left, right);
  }
  throw RuntimeError(*op, "Operator not found");
}

Object Interpreter::visitGetExp(Get *expr) {
  Object obj = evaluate(expr->object);
  if (obj.type == instance_type)
    return obj.instance->get(expr->name);
  throw RuntimeError(*expr->name, "Only instances have properties");
}

Object Interpreter::visitTernaryExp(Ternary *expr) {
  Object condition = evaluate(expr->condition);
  if (condition.type == bool_type) {
    if (condition.bool_literal)
      return evaluate(expr->expression1);
    else
      return evaluate(expr->expression2);
  } else {
    RuntimeError(*expr->op1, "Ternary Expression couldn't be evaluated");
  }
  return Object();
}

void Interpreter::visitClassStmnt(Class *stmnt) {
  environment->define(stmnt->name->lexeme, Object());
  Object klass(new CruxClass(stmnt->name->lexeme));
  environment->assign(stmnt->name, klass);
}
