//
// Created by Rohith on 1/29/24.
//
#include "Expr.h"
#include "cassert"

UnaryExp::UnaryExp(Token op, std::unique_ptr<Expr> right):
        op(op),
        right(std::move(right)){

    assert(this->right != nullptr);
}

std::any UnaryExp::accept(ExprVisitor<std::any> &visitor) const {
    return visitor.visitUnaryExp(*this);
}