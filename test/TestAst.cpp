//
// Created by Rohith on 1/29/24.
//
#include "gtest/gtest.h"
#include "PrettyPrinter.h"

TEST(AstPrinter, TestExpresson){
    std::shared_ptr<UnaryExp> uexp = std::make_shared<UnaryExp>(
                    Token{MINUS, "-", nullptr, 1},
                    std::make_shared<LiteralExp>(123.));

    std::shared_ptr<Expr> expression = std::make_shared<BinaryExp>(
            std::make_shared<UnaryExp>(
                    Token{MINUS, "-", nullptr, 1},
                    std::make_shared<LiteralExp>(123.)
            ),
            Token{STAR, "*", nullptr, 1},
            std::make_shared<GroupingExp>(
                    std::make_shared<LiteralExp>(45.67)));

    std::string result = AstPrinter{}.print(expression);
    ASSERT_EQ(uexp->op.type, MINUS);
}

