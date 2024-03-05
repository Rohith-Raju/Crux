//
// Created by Rohith on 2/23/24.
//

#include "Expr.h"

Expr::Expr(ExprType type) : type(type) {}

Expr::~Expr() {}

Binary::Binary(Expr *left, Token *op, Expr *right)
    : Expr(ExprType_Binary), left(left), op(op), right(right) {}

Binary::~Binary() {
  delete left;
  delete right;
  delete op;
}

Grouping::Grouping(Expr *expression)
    : Expr(ExprType_Grouping), expression(expression) {}

Grouping::~Grouping() { delete expression; }

Unary::Unary(Token *op, Expr *right)
    : Expr(ExprType_Unary), op(op), right(right) {}

Unary::~Unary() {
  delete right;
  delete op;
}

Literal::Literal(Object *literal) : Expr(ExprType_Literal), literal(literal) {}

Literal::~Literal() { delete literal; }
