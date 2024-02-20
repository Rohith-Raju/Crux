//
// Created by Rohith on 2/17/24.
//

#ifndef CRUX_INTERPRETER_H
#define CRUX_INTERPRETER_H

#include "Expr.h"

class Interpreter : public ExprVisitor{
private:
    std::any evaluate(std::shared_ptr<Expr> expr){
        expr->accept(*this);
    }

public:

    std::any visitLiteral(std::shared_ptr<LiteralExp> expr) override {
        return expr->literal;
    }
    std::any visitGroupExp(std::shared_ptr<GroupingExp> expr) override {
        return evaluate(expr->expression);
    }
};


#endif //CRUX_INTERPRETER_H
