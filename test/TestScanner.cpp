//
// Created by Rohith on 1/9/24.
//

#include "gtest/gtest.h"
#include "Scanner.h"

TEST(ScannerCheck, TestSingleToken){
    Scanner scan ("(");
    scan.scanTokens();
    ASSERT_EQ(scan.tokens.size(), 2);
    ASSERT_EQ(scan.tokens[0].type, LEFT_PAREN);
    ASSERT_EQ(scan.tokens[1].type, ENDOFFILE);
}

TEST(ScannerCheck, TestMultipleToken){
    Scanner scan ("(+{})");
    scan.scanTokens();
    ASSERT_EQ(scan.tokens.size(), 6);
    ASSERT_EQ(scan.tokens[0].type, LEFT_PAREN);
    ASSERT_EQ(scan.tokens[1].type, PLUS);
    ASSERT_EQ(scan.tokens[2].type, LEFT_BRACE);
    ASSERT_EQ(scan.tokens[3].type, RIGHT_BRACE);
    ASSERT_EQ(scan.tokens[4].type, RIGHT_PAREN);
    ASSERT_EQ(scan.tokens[5].type, ENDOFFILE);

}
