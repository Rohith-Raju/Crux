//
// Created by Rohith on 3/8/24
//

#include "Expr.h"
#include "Interpreter.h"
#include "gtest/gtest.h"

TEST(InterpreterCheck, TestInterpreter) {

  Expr *left = new Literal(new Object((double)10));

  Token *op = new Token(PLUS, "+", Object(), 1);

  Expr *right = new Literal(new Object((double)20));

  Expr *expression = new Binary(left, op, right);

  ASSERT_EQ(Interpreter{}.interpret(expression), "30.000000");
}

// todo: add more tests
