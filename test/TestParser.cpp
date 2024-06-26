//
// Created by Rohith on 2/13/24.
//
#include "AstPrinter.h"
#include "Parser.h"
#include "Scanner.h"
#include "Statement.h"
#include "gtest/gtest.h"
#include <vector>

TEST(ParserCheck, TestParserBasic) {
  std::string test = "10 + 20;";
  Scanner scan(test);
  std::vector<Token> tokens = scan.scanTokens();
  Parser p(tokens);
  std::vector<Statement *> statements = p.parse();
  Expression *exp = (Expression *)statements[0];
  ASSERT_EQ(PrettyPrint::print(exp->expression), "(+ 10.000000 20.000000)");
}

TEST(ParserCheck, TestParserComplex) {
  std::string test = "10 + (40 + (20 - 30) - 10) + 50;";
  Scanner scan(test);
  std::vector<Token> tokens = scan.scanTokens();
  Parser p(tokens);
  std::vector<Statement *> statements = p.parse();
  Expression *exp = (Expression *)statements[0];
  ASSERT_EQ(PrettyPrint::print(exp->expression),
            "(+ (+ 10.000000 (Group (- (+ 40.000000 (Group (- 20.000000 "
            "30.000000))) 10.000000))) 50.000000)");
}

TEST(ParserCheck, TestParserUnary) {
  std::string test = "!true;";
  Scanner scan(test);
  std::vector<Token> tokens = scan.scanTokens();
  Parser p(tokens);
  std::vector<Statement *> statements = p.parse();
  Expression *exp = (Expression *)statements[0];
  ASSERT_EQ(PrettyPrint::print(exp->expression), "(! true)");
}

TEST(ParserCheck, TestParserComplexUnary) {
  std::string test = "!true + (30 - false) + 40;";
  Scanner scan(test);
  std::vector<Token> tokens = scan.scanTokens();
  Parser p(tokens);
  std::vector<Statement *> statements = p.parse();
  Expression *exp = (Expression *)statements[0];
  ASSERT_EQ(PrettyPrint::print(exp->expression),
            "(+ (+ (! true) (Group (- 30.000000 false))) 40.000000)");
}

TEST(ParserCheck, TestParserTernary) {
  std::string test = "3 > 1 ? true : false;";
  Scanner scan(test);
  std::vector<Token> tokens = scan.scanTokens();
  Parser p(tokens);
  std::vector<Statement *> statements = p.parse();
  Expression *exp = (Expression *)statements[0];
  ASSERT_EQ(PrettyPrint::print(exp->expression),
            "(?: (> 3.000000 1.000000) true false)");
}
