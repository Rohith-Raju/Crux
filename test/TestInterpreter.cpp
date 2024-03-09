//
// Created by Rohith on 3/8/24
//
#include "Expr.h"
#include "Interpreter.h"
#include "Parser.h"
#include "Scanner.h"
#include "gtest/gtest.h"

TEST(InterpreterCheck, TestInterpreterBasic) {

  Expr *left = new Literal(new Object((double)10));

  Token *op = new Token(PLUS, "+", Object(), 1);

  Expr *right = new Literal(new Object((double)20));

  Expr *expression = new Binary(left, op, right);

  ASSERT_EQ(Interpreter{}.interpret(expression), "30.000000");
}

TEST(InterpreterTest, TestInterpreterFlow) {
  std::string test = "10 + (40 + (20 - 30) - 10) + 50";
  Scanner scan(test);
  std::vector<Token> tokens = scan.scanTokens();
  Parser p(tokens);
  Expr *expression = p.parse();
  ASSERT_EQ(Interpreter{}.interpret(expression), "80.000000");
}

TEST(InterpreterTest, TestInterpreterUnary) {
  std::string test = "!true";
  Scanner scan(test);
  std::vector<Token> tokens = scan.scanTokens();
  Parser p(tokens);
  Expr *expression = p.parse();
  ASSERT_EQ(Interpreter{}.interpret(expression), "false");
}

TEST(InterpreterTest, TestParserTernary) {
  std::string test = "3 > 1 ? true : false";
  Scanner scan(test);
  std::vector<Token> tokens = scan.scanTokens();
  Parser p(tokens);
  Expr *expression = p.parse();
  ASSERT_EQ(Interpreter{}.interpret(expression), "true");
}
