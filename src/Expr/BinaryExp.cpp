//
// Created by Rohith on 1/26/24.
//
#include "Expr.h"
#include "cassert"
BinaryExp::BinaryExp(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right):
        left(std::move(left)),
        op(op),
        right(std::move(right)){

    assert(this->left != nullptr);
    assert(this->right != nullptr);
}

std::any BinaryExp::accept(ExprVisitor<std::any> &visitor) const {
    return visitor.visitBinaryExp(*this);
}
