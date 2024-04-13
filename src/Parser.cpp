// Object
#include "Parser.h"
#include "Error.h"
#include "Expr.h"
#include "Statement.h"
#include "Token.h"
#include "utls/Object.h"
#include <vector>

std::vector<Statement *> Parser::parse() {
  std::vector<Statement *> statements;
  while (!isAtEnd()) {
    Statement *stmt = declaration();
    if (crux::hasError) {
      synchronize();
      if (stmt) {
        delete stmt;
      }
      stmt = nullptr;
      break;
    } else {
      statements.push_back(stmt);
    }
  }
  return statements;
}

Statement *Parser::declaration() {
  if (match(VAR))
    return varDeclaration();
  return statement();
}

Statement *Parser::varDeclaration() {
  Token *name = new Token(consume(IDENTIFIER, "variable name required"));

  Expr *initializer = nullptr;

  if (match(EQUAL)) {
    initializer = expression();
  }

  consume(SEMICOLON, "Expected ; after the variable declaration");
  return new Var(name, initializer);
}

Statement *Parser::statement() {
  if (match(PRINT))
    return printStatement();
  if (match(IF))
    return ifStatement();
  if (match(WHILE))
    return whileStatement();
  if (match(FOR))
    return forStatement();
  if (match(BREAK))
    return breakStatement();
  if (match(LEFT_BRACE))
    return new Block(blockStatement());
  return expressionStatement();
}
std::vector<Statement *> Parser::blockStatement() {
  std::vector<Statement *> stmnts;

  while (!check(RIGHT_BRACE) && !isAtEnd()) {
    stmnts.push_back(declaration());
  }

  consume(RIGHT_BRACE, "Expect closing } after the block");
  return stmnts;
}

Statement *Parser::ifStatement() {
  consume(LEFT_PAREN, "Expected ( after if");
  Expr *expr = expression();
  consume(RIGHT_PAREN, "Expected ) after if statement");

  Statement *thenBranch = statement();

  Statement *elseBranch = nullptr;
  if (match(ELSE)) {
    elseBranch = statement();
  }
  return new If(expr, thenBranch, elseBranch);
}

Statement *Parser::whileStatement() {
  consume(LEFT_PAREN, "Expected ( after while");
  Expr *expr = expression();
  consume(RIGHT_PAREN, "Expected ) after while");
  loopCounter++;
  Statement *body = statement();
  loopCounter--;
  return new While(expr, body);
}

Statement *Parser::forStatement() {
  consume(LEFT_PAREN, "expected ( after for");
  Statement *initializer;

  if (match(SEMICOLON))
    initializer = nullptr;
  else if (match(VAR))
    initializer = varDeclaration();
  else
    initializer = declaration();

  Expr *condition;
  if (match(SEMICOLON))
    condition = nullptr;
  else
    condition = expression();

  consume(SEMICOLON, "Expected ; after condition clause");

  Expr *increment;
  if (match(SEMICOLON))
    increment = nullptr;
  else
    increment = expression();

  consume(RIGHT_PAREN, "Expected ) after clause");

  Statement *body;
  body = statement();

  if (increment) {
    std::vector<Statement *> stmnts;
    stmnts.push_back(body);
    stmnts.push_back(new Expression(increment));
    body = new Block(stmnts);
  }

  if (!condition)
    Object *condition = new Object(true);

  body = new While(condition, body);

  if (initializer) {
    std::vector<Statement *> stmnts;
    stmnts.push_back(initializer);
    stmnts.push_back(body);
    body = new Block(stmnts);
  }
  return body;
}

Statement *Parser::breakStatement() {
  if (loopCounter == 0) {
    Token tkn = tokens[current];
    crux::error(tkn, "break should ony occur in for/while loops");
  }
  consume(SEMICOLON, "Expected ';' after 'break'.");
  return new Break(true);
}

Statement *Parser::printStatement() {
  Expr *expr = expression();
  consume(SEMICOLON, "Expected ; at the end of the statement");
  return new Print(expr);
}

Statement *Parser::expressionStatement() {
  Expr *expr = expression();
  consume(SEMICOLON, "Expected ; at the end of the statement");
  return new Expression(expr);
}

Expr *Parser::expression() { return assignment(); }

Expr *Parser::assignment() {
  Expr *expr = Or();

  if (match(EQUAL)) {
    Token equals = previous();
    Expr *value = assignment();
    if (expr->type == ExprType_Variable) {
      Variable *var = (Variable *)expr;
      Token *name = var->name;
      return new Assignment(name, value);
    }
    error(equals, "Invalid assignment target.");
  }
  return expr;
}

Expr *Parser::Or() {
  Expr *expr = And();

  while (match(OR)) {
    Token *op = new Token(previous());
    Expr *right = And();
    expr = new Logical(expr, op, right);
  }
  return expr;
}

Expr *Parser::And() {
  Expr *expr = ternary();

  while (match(AND)) {
    Token *op = new Token(previous());
    Expr *right = ternary();
    expr = new Logical(expr, op, right);
  }
  return expr;
}

Expr *Parser::ternary() {
  Expr *expr = equality();
  if (match(QUESTON_MARK)) {
    Token *questionMark = new Token(previous());
    Expr *expr1 = equality();
    if (match(COLON)) {
      Token *colon = new Token(previous());
      Expr *expr2 = equality();
      expr = new Ternary(expr, questionMark, expr1, colon, expr2);
    } else {
      error(peek(), "Expected:");
      delete questionMark;
      delete expr1;
    }
  }
  return expr;
}

Expr *Parser::equality() {
  Expr *expr = comparison();
  while (match(EQUAL_EQUAL, BANG_EQUAL)) {
    Token *op = new Token(previous());
    Expr *right = comparison();
    expr = new Binary(expr, op, right);
  }
  return expr;
}

Expr *Parser::comparison() {
  Expr *expr = term();
  while (match(GREATER, GREATER_EQUAL, LESS_EQUAL, LESS)) {
    Token *op = new Token(previous());
    Expr *right = term();
    expr = new Binary(expr, op, right);
  }
  return expr;
}

Expr *Parser::term() {
  Expr *expr = factor();
  while (match(MINUS, PLUS)) {
    Token *op = new Token(previous());
    Expr *right = factor();
    expr = new Binary(expr, op, right);
  }
  return expr;
}

Expr *Parser::factor() {
  Expr *expr = unary();
  while (match(SLASH, STAR)) {
    Token *op = new Token(previous());
    Expr *right = unary();
    expr = new Binary(expr, op, right);
  }
  return expr;
}

Expr *Parser::unary() {
  while (match(BANG, MINUS)) {
    Token *op = new Token(previous());
    Expr *right = primary();
    return new Unary(op, right);
  }
  return primary();
}

Expr *Parser::primary() {
  if (match(FALSE))
    return new Literal(new Object(false));

  if (match(TRUE))
    return new Literal(new Object(true));

  if (match(NIL))
    return new Literal(new Object());

  if (match(NUMBER)) {
    return new Literal(new Object(previous().literal));
  }

  if (match(STRING)) {
    return new Literal(new Object(previous().literal));
  }

  if (match(IDENTIFIER)) {
    return new Variable(new Token(previous()));
  }

  if (match(LEFT_PAREN)) {
    Expr *expr = expression();
    consume(RIGHT_PAREN, "Expect ')' after expression.");
    return new Grouping(expr);
  }
  throw error(peek(), "Expect expression.");
}

Token Parser::consume(TokenType type, std::string message) {
  if (check(type))
    return advance();

  throw error(peek(), message);
}

template <class... T> bool Parser::match(T... type) {
  if ((... || check(type))) {
    advance();
    return true;
  }
  return false;
}

bool Parser::check(TokenType type) {
  if (isAtEnd())
    return false;
  return peek().type == type;
}

Token Parser::advance() {
  if (!isAtEnd())
    ++current;
  return previous();
}

Token Parser::previous() { return tokens[current - 1]; }

Token Parser::peek() { return tokens[current]; }

Token Parser::peek_next() { return tokens[current + 1]; }

bool Parser::isAtEnd() { return peek().type == ENDOFFILE; }

typename Parser::ParseError Parser::error(Token token, std::string message) {
  crux::error(token, message);
  return ParseError("");
}

void Parser::synchronize() {
  advance();

  while (!isAtEnd()) {
    if (previous().type == SEMICOLON)
      return;
    switch (peek().type) {
    case CLASS:
    case FUN:
    case VAR:
    case FOR:
    case IF:
    case WHILE:
    case PRINT:
    case RETURN:
      return;
    }
    advance();
  }
}
