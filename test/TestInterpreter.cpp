//
#include "Expr.h"
#include "Interpreter.h"
#include "Parser.h"
#include "Scanner.h"
#include "gtest/gtest.h"
#include <Statement.h>
#include <string>
#include <vector>

TEST(InterpreterTest, TestExpression) {
  std::string test = "print(10 + (40 + (20 - 30) - 10) + 50);";
  Scanner scan(test);
  std::vector<Token> tokens = scan.scanTokens();
  Parser p(tokens);
  std::vector<Statement *> statements = p.parse();
  testing::internal::CaptureStdout();
  Interpreter{}.interpret(statements);
  std::string result = testing::internal::GetCapturedStdout();
  ASSERT_EQ(result, "80.000000\n");
}

TEST(InterpreterTest, TestUnaryExpression) {
  std::string test = "print(!true);";
  Scanner scan(test);
  std::vector<Token> tokens = scan.scanTokens();
  Parser p(tokens);
  std::vector<Statement *> statements = p.parse();
  testing::internal::CaptureStdout();
  Interpreter{}.interpret(statements);
  std::string result = testing::internal::GetCapturedStdout();
  ASSERT_EQ(result, "false\n");
}

TEST(InterpreterTest, TestTernaryExpression) {

  std::string test = "print(3 > 1 ? true : false);";
  Scanner scan(test);
  std::vector<Token> tokens = scan.scanTokens();
  Parser p(tokens);
  std::vector<Statement *> statements = p.parse();
  testing::internal::CaptureStdout();
  Interpreter{}.interpret(statements);
  std::string result = testing::internal::GetCapturedStdout();
  ASSERT_EQ(result, "true\n");
}

TEST(InterpreterTest, TestVarStatement) {
  std::string test = "var a = 10; print(a);";
  Scanner scan(test);
  std::vector<Token> token = scan.scanTokens();
  Parser parser(token);
  std::vector<Statement *> statement = parser.parse();
  testing::internal::CaptureStdout();
  Interpreter *interpreter = new Interpreter();
  interpreter->interpret(statement);
  std::string result = testing::internal::GetCapturedStdout();
  ASSERT_EQ(result, "10.000000\n");
}

TEST(InterpreterTest, TestIfStatement) {
  std::string test = "var a = 10; if(a>=10){print(\"equal\");}";
  Scanner scan(test);
  std::vector<Token> tokens = scan.scanTokens();
  Parser p(tokens);
  std::vector<Statement *> statements = p.parse();
  testing::internal::CaptureStdout();
  Interpreter *interpreter = new Interpreter();
  interpreter->interpret(statements);
  std::string result = testing::internal::GetCapturedStdout();
  ASSERT_EQ(result, "equal\n");
}

TEST(InterpreterTest, TestIfElseStatement) {
  std::string test =
      "var a = 15; if(a==10){print(\"equal\");} else{print(\"Not equal\");}";
  Scanner scan(test);
  std::vector<Token> tokens = scan.scanTokens();
  Parser p(tokens);
  std::vector<Statement *> statements = p.parse();
  testing::internal::CaptureStdout();
  Interpreter *interpreter = new Interpreter();
  interpreter->interpret(statements);
  std::string result = testing::internal::GetCapturedStdout();
  ASSERT_EQ(result, "Not equal\n");
  delete interpreter;
}

TEST(InterpreterTest, TestWhileLoop) {
  std::string test = "var a = 5; while(a > 0){ print(a); a = a-1;}";
  Scanner scan(test);
  std::vector<Token> tokens = scan.scanTokens();
  Parser p(tokens);
  std::vector<Statement *> statements = p.parse();
  testing::internal::CaptureStdout();
  Interpreter *interpreter = new Interpreter();
  interpreter->interpret(statements);
  std::string result = testing::internal::GetCapturedStdout();
  ASSERT_EQ(result, "5.000000\n4.000000\n3.000000\n2.000000\n1.000000\n");
}

TEST(InterpreterTest, TestForLoop) {
  std::string test = "for(var a = 0; a<5; a=a+1){print(a);}";
  Scanner scan(test);
  std::vector<Token> tokens = scan.scanTokens();
  Parser p(tokens);
  std::vector<Statement *> statements = p.parse();
  testing::internal::CaptureStdout();
  Interpreter *interpreter = new Interpreter();
  interpreter->interpret(statements);
  std::string result = testing::internal::GetCapturedStdout();
  ASSERT_EQ(result, "0.000000\n1.000000\n2.000000\n3.000000\n4.000000\n");
}

TEST(InterpreterTest, TestSimpleFunction) {
  std::string test = "fun printWords(a,b){print a +\" \"+ b;} "
                     "printWords(\"Hello\", \"World\");";
  Scanner scan(test);
  std::vector<Token> tokens = scan.scanTokens();
  Parser p(tokens);
  std::vector<Statement *> statements = p.parse();
  testing::internal::CaptureStdout();
  Interpreter *interpreter = new Interpreter();
  interpreter->interpret(statements);
  std::string result = testing::internal::GetCapturedStdout();
  ASSERT_EQ(result, "Hello World\n");
}
