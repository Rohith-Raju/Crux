
#ifndef CRUX_PRETTYPRINTER_H
#define CRUX_PRETTYPRINTER_H

#include "AstPrinter.h"
#include "Expr.h"
#include <sstream>
#include <string>

std::string PrettyPrint::parenthesize(std::string name, Expr *expr1,
                                      Expr *expr2, Expr *expr3, Expr *expr4) {

  std::stringstream builder;

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

std::string PrettyPrint::print(Expr *expr) { return visit(expr); }
std::string PrettyPrint::visitBinaryExp(Binary *expr) {
  return parenthesize(expr->op->lexeme, expr->left, expr->right);
}
std::string PrettyPrint::visitGroupExp(Grouping *expr) {
  return parenthesize("Group", expr->expression);
}
std::string PrettyPrint::visitUnaryExp(Unary *expr) {
  return parenthesize(expr->op->lexeme, expr->right);
}
std::string PrettyPrint::visitLiteral(Literal *expr) {
  std::string digits = expr->literal->str();
  return digits;
}

std::string PrettyPrint::visit(Expr *expr) {
  switch (expr->type) {
  case ExprType_Unary:
    return visitUnaryExp((Unary *)expr);
  case ExprType_Binary:
    return visitBinaryExp((Binary *)expr);
  case ExprType_Grouping:
    return visitGroupExp((Grouping *)expr);
  case ExprType_Literal:
    return visitLiteral((Literal *)expr);
  }
  return "<<Invalid type>>";
}

#endif // CRUX_PRETTYPRINTER_H
