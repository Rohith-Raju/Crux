//
// Created by Rohith on 2/17/24.
//

#ifndef CRUX_INTERPRETER_H
#define CRUX_INTERPRETER_H

#include "Error.h"
#include "Expr.h"
#include "utls/Object.h"
#include "utls/RuntimeError.h"

class Interpreter {
private:
  Object evaluate(Expr *expr) {
    switch (expr->type) {
    case ExprType_Binary:
      return visitBinaryExp((Binary *)expr);
    case ExprType_Unary:
      return visitUnaryExp((Unary *)expr);
    case ExprType_Literal:
      return visitLiteral((Literal *)expr);
    case ExprType_Grouping:
      return visitGroupExp((Grouping *)expr);
    }
    return Object();
  }

  bool isTruthy(Object right) {
    if (right.type == nullptr_type)
      return false;
    if (right.type == bool_type)
      return right.bool_literal;
    return true;
  }

  bool isEqual(Object left, Object right) {
    if (left.type == nullptr_type && right.type == nullptr_type)
      return true;
    if (left.type == nullptr_type)
      return false;

    return left.num_literal == right.num_literal;
  }

  void checkNumberOperand(Token *op, Object right) {
    if (right.type == num_type)
      return;
    RuntimeError(*op, "Operand must be a number");
  }
  void checkNumberOperands(Token *op, Object left, Object right) {
    if (left.type == num_type && right.type == num_type)
      return;
    throw RuntimeError(*op, "Operands must be numbers");
  }

public:
  std ::string interpret(Expr *expression) {
    try {
      Object expr = evaluate(expression);
      return expr.str();
    } catch (RuntimeError error) {
      crux::runtimeError(error);
    }
  }

  Object visitLiteral(Literal *expr) { return *expr->literal; }

  Object visitGroupExp(Grouping *expr) { return evaluate(expr->expression); }

  Object visitUnaryExp(Unary *expr) {
    Object right = evaluate(expr->right);
    switch (expr->op->type) {
    case BANG:
      return !isTruthy(right);
    case MINUS:
      checkNumberOperand(expr->op, right);
      return -right.num_literal;
    default:
      RuntimeError(*expr->op, "Invalid operator used");
    }
    return Object();
  }

  Object visitBinaryExp(Binary *expr) {
    Object left = evaluate(expr->left);
    Object right = evaluate(expr->right);
    Token *op = expr->op;
    switch (op->type) {
    case MINUS:
      checkNumberOperands(op, left, right);
      return left.num_literal - right.num_literal;
    case SLASH:
      checkNumberOperands(op, left, right);
      return left.num_literal / right.num_literal;
    case STAR:
      checkNumberOperands(op, left, right);
      return left.num_literal * right.num_literal;
    case PLUS:
      if (left.type == num_type && right.type == num_type)
        return left.num_literal + right.num_literal;
      if (left.type == string_type && right.type == string_type)
        return left.string_literal + right.string_literal;
      throw new RuntimeError(*op, "Operands must be two strings.");
    case GREATER:
      checkNumberOperands(op, left, right);
      return left.num_literal > right.num_literal;
    case GREATER_EQUAL:
      checkNumberOperands(op, left, right);
      return left.num_literal >= right.num_literal;
    case LESS:
      checkNumberOperands(op, left, right);
      return left.num_literal < right.num_literal;
    case LESS_EQUAL:
      checkNumberOperands(op, left, right);
      return left.num_literal <= right.num_literal;
    case BANG_EQUAL:
      return !isEqual(left, right);
    case EQUAL_EQUAL:
      return isEqual(left, right);
    }
    RuntimeError(*op, "Operator not found");
    return Object();
  }
};

#endif // CRUX_INTERPRETER_H
