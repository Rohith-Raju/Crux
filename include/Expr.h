//
// Created by Rohith on 1/25/24.
//

#ifndef CRUX_EXPR_H
#define CRUX_EXPR_H

#include <any>
#include <memory>
#include <cassert>
#include <type_traits>
#include "Token.h"

class BinaryExp;
class GroupingExp;
class UnaryExp;
class LiteralExp;

class ExprVisitor{
public:
    ~ExprVisitor() = default;
    virtual std::any visitBinaryExp(std::shared_ptr<BinaryExp> expr) = 0;
    virtual std::any visitGroupExp(std::shared_ptr<GroupingExp> expr) = 0;
    virtual std::any visitUnaryExp(std::shared_ptr<UnaryExp> expr) = 0;
    virtual std::any visitLiteral(std::shared_ptr<LiteralExp> expr) = 0;

};

class Expr{
public:
    virtual std::any accept(ExprVisitor &visitor) = 0;
};

class BinaryExp: public Expr, public std::enable_shared_from_this<BinaryExp>{
public:
    std::shared_ptr<Expr> left;
    Token op;
    std::shared_ptr<Expr> right;

    BinaryExp(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right):
        left(std::move(left)),
        op(std::move(op)),
        right(std::move(right)){

            assert(this->left != nullptr);
            assert(this->right != nullptr);
    }
    std::any accept(ExprVisitor &visitor) override {
        return visitor.visitBinaryExp(shared_from_this());
    }

};

class GroupingExp: public Expr, public std::enable_shared_from_this<GroupingExp> {
public:
    std::shared_ptr<Expr> expr;

    GroupingExp(std::shared_ptr<Expr> expr):expr(std::move(expr)){
        assert(this->expr != nullptr);
    }
    std::any accept(ExprVisitor& visitor) override {
        return visitor.visitGroupExp(shared_from_this());
    };

};

class UnaryExp : public Expr, public std::enable_shared_from_this<UnaryExp> {
public:
    Token op;
    std::shared_ptr<Expr> right;

    UnaryExp(Token op, std::shared_ptr<Expr> right):op(std::move(op)),right(std::move(right)){
        assert(this->right != nullptr);
    }

    std::any accept(ExprVisitor& visitor) override {
        return visitor.visitUnaryExp(shared_from_this());
    }
};

class LiteralExp : public Expr, public std::enable_shared_from_this<LiteralExp> {
public:
    object literal;
    LiteralExp(object literal):literal(std::move(literal)){}
    std::any accept(ExprVisitor& visitor) override {
        return visitor.visitLiteral(shared_from_this());
    }
};


#endif //CRUX_EXPR_H
