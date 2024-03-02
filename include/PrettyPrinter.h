//
// Created by Rohith on 1/30/24.
//

#ifndef CRUX_PRETTYPRINTER_H
#define CRUX_PRETTYPRINTER_H

#include "Expr.h"
#include "cassert"
#include "sstream"

namespace AstPrinter {

std::string visit(Expr *expr);

std::string parenthesize(std::string name, Expr *expr1 = 0, Expr *expr2 = 0,
                         Expr *expr3 = 0, Expr *expr4 = 0) {
  std::ostringstream builder;

  builder << "(" << name;
  if (expr1)
    builder << " " << visit(expr1);
  if (expr2)
    builder << " " << visit(expr2);
  if (expr3)
    builder << " " << visit(expr3);
  if (expr4)
    builder << " " << visit(expr4);
  builder << ")";

  return builder.str();
}

std::string print(Expr *expr) { return visit(expr); }
std::string visitBinaryExp(Binary *expr) {
  return parenthesize(expr->op->lexeme, expr->left, expr->right);
}
std::string visitGroupExp(Grouping *expr) {
  return parenthesize("group", expr->expression);
}
std::string visitUnaryExp(Unary *expr) {
  return parenthesize(expr->op->lexeme, expr->right);
}
std::string visitLiteral(Literal *expr) { return expr->literal->str(); }

std::string visit(Expr *expr) {
  switch (expr->type) {
  case ExprType_Unary:
    visitUnaryExp((Unary *)expr);
    break;
  case ExprType_Binary:
    visitBinaryExp((Binary *)expr);
    break;
  case ExprType_Grouping:
    visitGroupExp((Grouping *)expr);
    break;
  case ExprType_Literal:
    visitLiteral((Literal *)expr);
    break;
  }
  return "<<Invalid type>>";
}
}; // namespace AstPrinter

#endif // CRUX_PRETTYPRINTER_H
