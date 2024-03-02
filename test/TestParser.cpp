//
// Created by Rohith on 2/13/24.
//
#include "Parser.h"
#include "PrettyPrinter.h"
#include "Scanner.h"
#include "gtest/gtest.h"

TEST(ParserCheck, TestParserBasic) {
  std::string test = "10 + 20";
  Scanner scan(test);
  std::vector<Token> tokens = scan.scanTokens();
  Parser p(tokens);
  Expr *expression = p.parse();
  ASSERT_EQ(AstPrinter::print(expression), "(+ 10.000000 20.000000)");
}

TEST(ParserCheck, TestParserComplex) {
  std::string test = "10 + (40 + (20 - 30) - 10) + 50";
  Scanner scan(test);
  std::vector<Token> tokens = scan.scanTokens();
  Parser p(tokens);
  Expr *expression = p.parse();
  ASSERT_EQ(AstPrinter::print(expression),
            "(+ (+ 10.000000 (Group (- (+ 40.000000 (Group (- 20.000000 "
            "30.000000))) 10.000000))) 50.000000)");
}

TEST(ParserCheck, TestParserUnary) {
  std::string test = "!true";
  Scanner scan(test);
  std::vector<Token> tokens = scan.scanTokens();
  Parser p(tokens);
  Expr *expression = p.parse();
  ASSERT_EQ(AstPrinter::print(expression), "(! true)");
}

TEST(ParserCheck, TestParserComplexUnary) {
  std::string test = "!true + (30 - false) + 40";
  Scanner scan(test);
  std::vector<Token> tokens = scan.scanTokens();
  Parser p(tokens);
  Expr *expression = p.parse();
  ASSERT_EQ(AstPrinter::print(expression),
            "(+ (+ (! true) (Group (- 30.000000 false))) 40.000000)");
}
