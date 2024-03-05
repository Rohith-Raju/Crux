//
// Created by Rohith on 1/29/24.
//
#include "AstPrinter.h"
#include "Expr.h"
#include "Token.h"
#include "utls/Object.h"
#include "gtest/gtest.h"

TEST(AstPrinterCheck, TestExpresson) {

  Expr *left_exp = new Grouping(new Literal(new Object((double)10)));

  Token *op = new Token(STAR, "*", Object(), 1);

  Expr *right_exp = new Unary(new Token(MINUS, "-", Object(), 1),
                              new Literal(new Object((double)20)));

  Expr *expression = new Binary(left_exp, op, right_exp);
  PrettyPrint::print(expression);

  ASSERT_EQ(PrettyPrint::print(expression),
            "(* (Group 10.000000) (- 20.000000))");
}
