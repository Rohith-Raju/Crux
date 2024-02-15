//
// Created by Rohith on 1/30/24.
//

#ifndef CRUX_PRETTYPRINTER_H
#define CRUX_PRETTYPRINTER_H

#include "Expr.h"
#include "sstream"
#include "cassert"

class AstPrinter : public ExprVisitor{
private:
    template <class... E>
    std::string parenthesize(std::string_view name, E... expr)
    {
        std::ostringstream builder;

        builder << "(" << name;
        ((builder << " " << print(expr)), ...);
        builder << ")";

        return builder.str();
    }
public:
    std::string print(std::shared_ptr<Expr> expr){
        return std::any_cast<std::string>(expr->accept(*this));
    }
    std::any visitBinaryExp(std::shared_ptr<BinaryExp> expr) override {
        return parenthesize(expr->op.lexeme,
                            expr->left, expr->right);
    }
    std::any visitGroupExp(std::shared_ptr<GroupingExp> expr) override {
        return parenthesize("Group",expr->expr);
    }
    std::any visitUnaryExp(std::shared_ptr<UnaryExp> expr) override {
        return parenthesize(expr->op.lexeme, expr->right);
    }
    std::any visitLiteral(std::shared_ptr<LiteralExp> expr) override {

        object literal = expr->literal;

        if (std::get_if<std::string>(&literal)){
            return "nil";
        } else if (std::string* string_data =  std::get_if<std::string>(&literal)) {
            return *string_data;
        } else if (double* double_data =  std::get_if<double>(&literal)) {
            return std::to_string(*double_data);
        } else if (bool* bool_data =  std::get_if<bool>(&literal)) {
            return *bool_data ? std::string ("true"): std::string("false");
        }
        return "Error in visitLiteralExpr: literal type not recognized.";
    }

};


#endif //CRUX_PRETTYPRINTER_H
