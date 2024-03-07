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

  ASSERT_EQ(PrettyPrint::print(expression),
            "(* (Group 10.000000) (- 20.000000))");
}

TEST(AstPrinterCheck, TestTernary) {

  Expr *left = new Literal(new Object((double)20));

  Token *op = new Token(GREATER, ">", Object(), 1);

  Expr *right = new Literal(new Object((double)10));

  Expr *condition = new Binary(left, op, right);

  Token *op1 = new Token(QUESTON_MARK, "?", Object(), 1);

  Expr *expr1 = new Literal(new Object(bool(true)));

  Token *op2 = new Token(COLON, ":", Object(), 1);

  Expr *expr2 = new Literal(new Object(bool(false)));

  Expr *expression = new Ternary(condition, op1, expr1, op2, expr2);

  ASSERT_EQ(PrettyPrint::print(expression),
            "(?: (> 20.000000 10.000000) true false)");
}
