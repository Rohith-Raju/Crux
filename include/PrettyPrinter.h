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
    std::string print(Expr* expr){
        return vist(expr);
    }
     std::string visitBinaryExp(Expr* expr)  {
        return parenthesize();
    }
    std::string visitGroupExp(std::shared_ptr<GroupingExp> expr)  {
        return parenthesize();
    }
    std::string visitUnaryExp(Unary* expr)  {
        return parenthesize();
    }
    std::string visitLiteral(Literal* expr)  {
        return expr->literal->str();
    }

    std::string vist(Expr* expr)

};


#endif //CRUX_PRETTYPRINTER_H
