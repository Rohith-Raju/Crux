//
// Created by Rohith on 1/3/24.
//

#ifndef CRUX_TOKEN_H
#define CRUX_TOKEN_H

#include <string>
#include <map>

enum TokenType {
    // Single-character tokens.
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

    // One or two character tokens.
    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,

    // Literals.
    IDENTIFIER, STRING, NUMBER,

    // Keywords.
    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
    PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

    ENDOFFILE
};

struct null{};

using object = std::variant<null,size_t,std::string>;


class Token {
public:
    TokenType type;
    std::string lexeme;
    object literal;
    int line;

    Token(TokenType type, std::string lexeme,object literal, int line ):type(type),lexeme(lexeme),literal(literal),line(line)
    {}
};

#endif //CRUX_TOKEN_H
