//
// Created by Rohith on 1/29/24.
//
#include "Expr.h"
#include "cassert"

GroupingExp::GroupingExp(std::unique_ptr<Expr> expr):
        expr(std::move(expr)){

    assert(expr != nullptr);
}

std::any GroupingExp::accept(ExprVisitor<std::any> &visitor) const {
    return visitor.visitGroupExp(*this);
}