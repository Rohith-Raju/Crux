//
// Created by Rohith on 1/25/24.
//

#ifndef CRUX_EXPR_H
#define CRUX_EXPR_H

#include <any>
#include <memory>
#include "Token.h"

class BinaryExp;
class GroupingExp;
class UnaryExp;
class LiteralExp;

template <typename T>
class ExprVisitor{
public:
    ~ExprVisitor() = default;

    virtual T visitBinaryExp(const BinaryExp &expr) = 0;
    virtual T visitGroupExp(const GroupingExp &expr) = 0;
    virtual T visitUnaryExp(const UnaryExp &expr) = 0;
    virtual T visitLiteral(const LiteralExp &expr) = 0;

};


class Expr{
public:
    virtual ~Expr() = default;
    virtual std::any accept(ExprVisitor<std::any> &visitor) const;
};

class BinaryExp: public Expr{
private:
    std::unique_ptr<Expr> left;
    Token op;
    std::unique_ptr<Expr> right;

public:
    BinaryExp(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right);
    std::any accept(ExprVisitor<std::any> &visitor) const override;

    const Expr& getLeft() const {return *left;}
    const Token& getOperator() const {return op;}
    const Expr& getRight() const {return *right;}
};

class GroupingExp: public Expr {
private:
    std::unique_ptr<Expr> expr;

public:
    GroupingExp(std::unique_ptr<Expr> expr);
    std::any accept(ExprVisitor<std::any>& visitor) const override;

    const Expr& getExpr() const { return *expr; }

};

class UnaryExp : public Expr {
private:
    Token op;
    std::unique_ptr<Expr> right;

public:
    UnaryExp(Token op, std::unique_ptr<Expr> right);
    std::any accept(ExprVisitor<std::any>& visitor) const override;

    const Token& getOp() const { return op; }
    const Expr& getRightExpr() const { return *right; }

};

class LiteralExp : public Expr {
private:
    std::any literal;
public:
    LiteralExp(std::any literal);
    std::any accept(ExprVisitor<std::any>& visitor) const override;

    const std::any& getLiteral() const { return literal; }
};


#endif //CRUX_EXPR_H
