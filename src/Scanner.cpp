//
// Created by Rohith on 1/3/24.
//

#include "Scanner.h"


bool Scanner::isAtEnd() {
    return current >= source.length();
}

char Scanner::advance() {
    return source[current++];
}

std::vector<Token> Scanner::scanTokens() {
    tkn::initializeKeywords();
    while(!isAtEnd()) {
        start = current;
        scanToken();
    }
    tokens.push_back(Token(ENDOFFILE, "" , null{}, line));
    return tokens;
}

void Scanner::scanToken() {
    char c = advance();
    switch (c) {
        case '(':
            addToken(LEFT_PAREN);
            break;
        case ')':
            addToken(RIGHT_PAREN);
            break;
        case '{':
            addToken(LEFT_BRACE);
            break;
        case '}':
            addToken(RIGHT_BRACE);
            break;
        case ',':
            addToken(COMMA);
            break;
        case '.':
            addToken(DOT);
            break;
        case '-':
            addToken(MINUS);
            break;
        case '+':
            addToken(PLUS);
            break;
        case ';':
            addToken(SEMICOLON);
            break;
        case '*':
            addToken(STAR);
            break;
        case '!':
            addToken(match('=') ? BANG_EQUAL: BANG);
            break;
        case '=':
            addToken(match('=') ? EQUAL_EQUAL: EQUAL);
            break;
        case '<':
            addToken(match('=') ? LESS_EQUAL: LESS);
            break;
        case '>':
            addToken(match('=') ? GREATER_EQUAL: GREATER);
            break;
        case'/':
            if (match('/')) {
                // A comment goes until the end of the line.
                while (peek() != '\n' && !isAtEnd()) advance();
            } else {
                addToken(SLASH);
            }
            break;
        case ' ':
        case '\r':
        case '\t':
            break;
        case'\n':
            line++;
            break;
        case '"':
            string();
        default:
            if(isDigit(c)){
                number();
            }
            if(isAlpha(c)){
                identifier();
            }
            else{
                error(line,"Unexpected character");
            }
    }

}

void Scanner::string(){
    while(peek() != '"' && !isAtEnd()){
        if(peek() == '\n') line++;
        advance();
    }
    if (isAtEnd()) {
       error(line, "Unterminated string");
    }
    advance();
    std::string value = source.substr(start+1, current-1);
    addToken(STRING, value);
}

void Scanner::addToken(TokenType type) {
    addToken(type, null{});
}

void Scanner::addToken(TokenType type, Literal literal){
    std::string text = source.substr(start, current);
    tokens.push_back(Token(type,text,literal,line));

}

bool Scanner::match(char expected) {
    if (isAtEnd()) return false;
    if(source[current] != expected) return false;
    current++;
    return true;
}

bool Scanner::isDigit(char c) {
    return c > '0' && c <='9';
}

bool Scanner::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') ||
            c == '_';
}

void Scanner::number() {
    while(isDigit(peek())) advance();
    if(peek() == '.' && !isDigit(peekNext())){
        advance();
        while (isDigit(peek())) advance();
    }
    size_t num;
    std::stoi(source.substr(start,current), &num);
    addToken(NUMBER, num);
}

bool Scanner::isAlphaNumeric(char c) {
    return isAlpha(c) || isDigit(c);
}

void Scanner::identifier() {
    while (isAlphaNumeric(peek())) advance();
    std::string text = source.substr(start,current);
    if(tkn::keywords[text]) addToken(tkn::keywords[text]);
    else addToken(IDENTIFIER);
}

char Scanner::peek() {
    if(isAtEnd()) return '\0';
    return source[current];
}

char Scanner::peekNext() {
    if(source[current + 1] >= source.length()) return '\0';
    return source[current + 1];
};

void tkn::initializeKeywords() {
    keywords["and"] = AND;
    keywords["class"] = CLASS;
    keywords["else"] = ELSE;
    keywords["false"] = FALSE;
    keywords["for"] = FOR;
    keywords["fun"] = FUN;
    keywords["if"] = IF;
    keywords["nil"] = NIL;
    keywords["or"] = OR;
    keywords["print"] = PRINT;
    keywords["return"] = RETURN;
    keywords["super"] = SUPER;
    keywords["this"] = THIS;
    keywords["true"] = TRUE;
    keywords["var"] = VAR;
    keywords["while"] = WHILE;
}