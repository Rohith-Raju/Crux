//
// Created by Rohith on 2/9/24.
//
#include "Parser.h"

Parser::Parser(std::vector<Token> tokens) : tokens(tokens){};

std::shared_ptr<Expr> Parser::expression() {
    return equality();
}

std::shared_ptr<Expr> Parser::equality() {
    std::shared_ptr<Expr> expr = comparison();
    while (match(EQUAL_EQUAL, BANG_EQUAL)){
        Token op = previous();
        std::shared_ptr right = comparison();
        expr = std::make_shared<BinaryExp>(expr, op, right);
    }
    return expr;
}

std::shared_ptr<Expr> Parser::comparison() {
    std::shared_ptr<Expr> expr = term();
    while (match(GREATER, GREATER_EQUAL, LESS_EQUAL, LESS)){
        Token op = previous();
        std::shared_ptr right = term();
        expr = std::make_shared<BinaryExp>(expr, std::move(op), right);
    }
    return expr;
}

std::shared_ptr<Expr> Parser::term() {
    std::shared_ptr<Expr> expr = factor();
    while (match(MINUS, PLUS)){
        Token op = previous();
        std::shared_ptr right = factor();
        expr = std::make_shared<BinaryExp>(expr, std::move(op), right);
    }
    return expr;
}

std::shared_ptr<Expr> Parser::factor() {
    std::shared_ptr<Expr> expr = unary();
    while (match(SLASH, STAR)){
        Token op = previous();
        std::shared_ptr right = unary();
        expr = std::make_shared<BinaryExp>(expr, std::move(op), right);
    }
    return expr;
}

std::shared_ptr<Expr> Parser::unary() {
    while (match(BANG, MINUS)){
        Token op = previous();
        std::shared_ptr right = primary();
        return std::make_shared<UnaryExp>(std::move(op), right);
    }
    return primary();
}

std::shared_ptr<Expr> Parser::primary() {
    if (match(FALSE)) return std::make_shared<LiteralExp>(false);
    if (match(TRUE)) return std::make_shared<LiteralExp>(true);
    if (match(NIL)) return std::make_shared<LiteralExp>(nullptr);

    if (match(NUMBER, STRING)) {
        return std::make_shared<LiteralExp>(previous().literal);
    }

    if (match(LEFT_PAREN)) {
        std::shared_ptr<Expr> expr = expression();
        consume(RIGHT_PAREN, "Expect ')' after expression.");
        return std::make_shared<GroupingExp>(expr);
    }
    //todo: add parser error handling
    error(peek().line, "Expect expression.");

}

template<class ...T>
bool Parser::match(T ...type) {
    assert((... && std::is_same_v<T,TokenType>));
    if((... || check(type))){
        advance();
        return true;
    }
    return false;
}

bool Parser::check(TokenType type) {
    if(isAtEnd()) return false;
    return peek().type == type;
}

Token Parser::advance() {
    if(!isAtEnd()) ++current;
    return previous();
}

Token Parser::previous() {
    return tokens[current - 1];
}

Token Parser::peek() {
    return tokens[current++];
}
