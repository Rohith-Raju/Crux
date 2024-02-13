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
struct ParseError: public std::runtime_error {
    using std::runtime_error::runtime_error;
};
    std::vector<Token> tokens;
    int current = 0;
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
    Token consume(TokenType type, std::string message);
    template<class... T>
    bool match(T... type);
    ParseError error(Token token, std::string message);
    void synchronize();
public:
    Parser(const std::vector<Token>& tokens)
            : tokens{tokens}{};
    std::shared_ptr<Expr>parse();
};

#endif //CRUX_PARSER_H
