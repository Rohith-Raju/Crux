//
// Created by Rohith on 3/8/24
//
#include "Expr.h"
#include "Interpreter.h"
#include "Parser.h"
#include "Scanner.h"
#include "gtest/gtest.h"
#include <Statement.h>
#include <iostream>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <vector>

TEST(InterpreterTest, TestInterpreterExpression) {
  std::string test = "10 + (40 + (20 - 30) - 10) + 50;";
  Scanner scan(test);
  std::vector<Token> tokens = scan.scanTokens();
  Parser p(tokens);
  std::vector<Statement *> statements = p.parse();
  testing::internal::CaptureStdout();
  Interpreter{}.interpret(statements);
  std::string result = testing::internal::GetCapturedStdout();
  ASSERT_EQ(result, "80.000000\n");
}

TEST(InterpreterTest, TestInterpreterUnaryExpression) {
  std::string test = "!true;";
  Scanner scan(test);
  std::vector<Token> tokens = scan.scanTokens();
  Parser p(tokens);
  std::vector<Statement *> statements = p.parse();
  testing::internal::CaptureStdout();
  Interpreter{}.interpret(statements);
  std::string result = testing::internal::GetCapturedStdout();
  ASSERT_EQ(result, "false\n");
}

TEST(InterpreterTest, TestParserTernaryExpression) {
  std::string test = "3 > 1 ? true : false;";
  Scanner scan(test);
  std::vector<Token> tokens = scan.scanTokens();
  Parser p(tokens);
  std::vector<Statement *> statements = p.parse();
  testing::internal::CaptureStdout();
  Interpreter{}.interpret(statements);
  std::string result = testing::internal::GetCapturedStdout();
  ASSERT_EQ(result, "true\n");
}

TEST(InterpreterTest, TestInterpreterVarStatement) {

  std::string test = "var a = 10; print(a);";
  std::string test_f = "a = 10"; // fails

  Scanner scan(test);
  Scanner scan_f(test_f);

  std::vector<Token> token = scan.scanTokens();
  std::vector<Token> token_f = scan_f.scanTokens();

  Parser parser(token);
  Parser parser_f(token_f);

  std::vector<Statement *> statement = parser.parse();

  std::stringstream buffer;
  std::streambuf *sbuf = std::cout.rdbuf();
  std::cout.rdbuf(buffer.rdbuf());
  Interpreter{}.interpret(statement);
  std::cout.rdbuf(sbuf);
  ASSERT_EQ(buffer.str(), "10.000000\n");

  EXPECT_THROW(parser_f.parse(), std::runtime_error);
}
