//
// Created by Rohith on 1/29/24.
//
#include "gtest/gtest.h"
#include "PrettyPrinter.h"
TEST(AstPrinter, TestExpresson){
    std::shared_ptr<Expr> expr = std::make_shared<Unary>(
            Token{MINUS, "-", {}, 1},
            std::make_shared<Literal>(123.));
    std::shared_ptr<Expr> expression = std::make_shared<Binary>(
            std::make_shared<Unary>(
                    Token{MINUS, "-", {}, 1},
                    std::make_shared<Literal>(123.)
            ),
            Token{STAR, "*", {}, 1},
            std::make_shared<Grouping>(
                    std::make_shared<Literal>(45.67)));
    ASSERT_EQ( AstPrinter{}.print(expr),"");
}