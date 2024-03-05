#ifndef CRUX_ASTPRINTER_H
#define CRUX_ASTPRINTER_H

#include "Expr.h"
#include <string>

namespace PrettyPrint {

std::string visit(Expr *expr);

std::string parenthesize(std::string name, Expr *expr1 = 0, Expr *expr2 = 0,
                         Expr *expr3 = 0, Expr *expr4 = 0);

std::string print(Expr *expr);

std::string visitBinaryExp(Binary *expr);

std::string visitGroupExp(Grouping *expr);

std::string visitUnaryExp(Unary *expr);

std::string visitLiteral(Literal *expr);

} // namespace PrettyPrint

#endif
