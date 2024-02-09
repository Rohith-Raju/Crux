//
// Created by Rohith on 2/9/24.
//

#ifndef CRUX_PARSER_H
#define CRUX_PARSER_H

#include <memory>
#include <cassert>
#include <utility> //std::move()
#include <vector>
#include "Expr.h"
#include "Token.h"
#include "Error.h"



class Parser{
private:
    std::vector<Token> tokens;
    int current = 0;
    Parser(std::vector<Token> tokens);
    std::shared_ptr<Expr> expression();
    std::shared_ptr<Expr> comparison();
    std::shared_ptr<Expr> term();
    std::shared_ptr<Expr> factor();
    std::shared_ptr<Expr> unary();
    std::shared_ptr<Expr> primary();

    //helper functions
    std::shared_ptr<Expr> equality();
    bool check(TokenType type);
    Token advance();
    bool isAtEnd();
    Token peek();
    Token previous();
    Token consume(TokenType type, const char* message);
    template<class... T>
    bool match(T... type);
public:
    std::shared_ptr<Expr>parse();
};

#endif //CRUX_PARSER_H
