//
// Created by Rohith on 1/29/24.
//
#include "Expr.h"
#include "cassert"

LiteralExp::LiteralExp(std::any literal):literal(std::move(literal)){}

std::any LiteralExp::accept(ExprVisitor<std::any> &visitor) const {
    return visitor.visitLiteral(*this);
}