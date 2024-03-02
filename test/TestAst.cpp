//
// Created by Rohith on 1/29/24.
//
#include "Expr.h"
#include "PrettyPrinter.h"
#include "Token.h"
#include "utls/Object.h"
#include "gtest/gtest.h"

TEST(AstPrinterCheck, TestExpresson) {
  Expr *right_exp = new Unary(new Token(MINUS, "-", Object(), 1),
                              new Literal(new Object((double)20)));

  Token *op = new Token(STAR, "*", Object(), 1);

  Expr *left_exp = new Grouping(new Literal(new Object((double)10)));

  Expr *expression = new Binary(right_exp, op, left_exp);

  ASSERT_EQ(AstPrinter::print(expression), "");
}
