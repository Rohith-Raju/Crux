//
// Created by Rohith on 2/23/24.
//

#include "Expr.h"
#include <vector>

Expr::Expr(ExprType type) : type(type) {}
Token *op = new Token(STAR, "*", Object(), 1);

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

Call::Call(Expr *callee, Token *op, std::vector<Expr *> arguments)
    : Expr(ExprType_Call), callee(callee), paren(op), arguments(arguments) {}

Call::~Call() {
  delete callee;
  delete paren;
}

Unary::Unary(Token *op, Expr *right)
    : Expr(ExprType_Unary), op(op), right(right) {}

Unary::~Unary() {
  delete right;
  delete op;
}

Ternary::Ternary(Expr *condt, Token *op1, Expr *expr1, Token *op2, Expr *expr2)
    : Expr(ExprType_Ternary), condition(condt), op1(op1), expression1(expr1),
      op2(op2), expression2(expr2) {}

Ternary::~Ternary() {
  delete condition;
  delete op1;
  delete expression1;
  delete op2;
  delete expression2;
}

Logical::Logical(Expr *left, Token *op, Expr *right)
    : Expr(ExprType_Logical), left(left), op(op), right(right) {}

Logical::~Logical() {
  delete left;
  delete op;
  delete right;
}

Literal::Literal(Object *literal) : Expr(ExprType_Literal), literal(literal) {}

Literal::~Literal() { delete literal; }

Variable::Variable(Token *name) : Expr(ExprType_Variable), name(name) {}

Variable::~Variable() { delete name; }

Assignment::Assignment(Token *name, Expr *value)
    : Expr(ExprType_Assignment), name(name), value(value) {}

Assignment::~Assignment() {
  delete name;
  delete value;
}

Get::Get(Token *name, Expr *object)
    : Expr(ExprType_Get), name(name), object(object) {}

Get::~Get() {
  delete name;
  delete object;
}

Set::Set(Expr *object, Token *name, Expr *value)
    : Expr(ExprType_Set), object(object), name(name), value(value) {}

Set::~Set() {
  delete object;
  delete name;
  delete value;
}
