//
// Created by Rohith on 2/17/24.
//

#ifndef CRUX_INTERPRETER_H
#define CRUX_INTERPRETER_H

#include "Error.h"
#include "Expr.h"
#include "utls/Object.h"
#include "utls/RuntimeError.h"
#include <string>

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
    case ExprType_Ternary:
      return visitTernaryExp((Ternary *)expr);
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
  bool checkIfSameTypes(Object left, Object right) {
    if (left.type == num_type && right.type == num_type)
      return true;
    else
      return false;
  }

  bool checkCompatibility(Token *op, Object left, Object right) {
    if ((left.type == string_type && right.type == num_type) ||
        left.type == num_type && right.type == string_type) {
      return true;
    } else {
      return false;
    }
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
    RuntimeError(*op, "Operator not found");
  }

  Object visitTernaryExp(Ternary *expr) {
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
};

#endif // CRUX_INTERPRETER_H
