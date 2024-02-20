//
// Created by Rohith on 1/3/24.
//

#ifndef CRUX_SCANNER_H
#define CRUX_SCANNER_H

#include "Token.h"
#include "Error.h"
#include <vector>

namespace tkn {
    static std::map<std::string, TokenType> keywords;

    void initializeKeywords();
}

class Scanner{
public:
    std::string source;
    std::vector<Token> tokens;
    int start = 0;
    int current = 0;
    int line = 0;
    Scanner(std::string source):source(source){};
    bool isAtEnd();
    bool match(char expected);
    bool isDigit(char c);
    bool isAlpha(char c);
    bool isAlphaNumeric(char c);
    char peekNext();
    std::vector<Token> scanTokens();
    char peek();
    void string();
    void number();
    char advance();
    void scanToken();
    void identifier();
    void addToken(TokenType type);
    void addNumber(double num);
    void addString(std::string string);
};

#endif //CRUX_SCANNER_H
