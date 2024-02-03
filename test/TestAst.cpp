//
// Created by Rohith on 1/29/24.
//
#include "gtest/gtest.h"
#include "PrettyPrinter.h"

TEST(AstPrinter, TestExpresson){
    std::shared_ptr<Expr> expression = std::make_shared<BinaryExp>(
            std::make_shared<UnaryExp>(
                    Token{MINUS, "-", {}, 1},
                    std::make_shared<LiteralExp>(123.)
            ),
            Token{STAR, "*", {}, 1},
            std::make_shared<GroupingExp>(
                    std::make_shared<LiteralExp>(45.67)));
    ASSERT_EQ( AstPrinter{}.print(expression),"(* (- 123.000000) (Group 45.670000))");
}