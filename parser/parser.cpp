#include "parser.h"
#include "../token/token.h"
#include <stdio.h>
#include <string>

Parser::Parser(const std::vector<Token> &tokens) : tokens(tokens), current(0) {}

std::vector<std::unique_ptr<Stmt>> Parser::parseProgram() {
  std::vector<std::unique_ptr<Stmt>> statements;
  while (!isAtEnd()) {
    statements.push_back(declaration());
  }
  return statements;
}

std::unique_ptr<Stmt> Parser::declaration() {
  if (match({TokenType::LET}))
    return varDeclaration();
  return statement();
}

std::unique_ptr<Stmt> Parser::varDeclaration() {
  Token name = consume(TokenType::IDENTIFIER, "Expect variable name.");

  std::unique_ptr<Expr> initializer = nullptr;
  if (match({TokenType::EQUALS})) {
    initializer = expression();
  }
  consume(TokenType::SEMICOLON, "Expect ';' after variable declaration.");
  return std::make_unique<VarStmt>(name, std::move(initializer));
}

std::unique_ptr<Stmt> Parser::statement() {
  if (match({TokenType::PRINT}))
    return printStatement();
  auto expr = expression();
  consume(TokenType::SEMICOLON, "Expect ';' after expression.");
  return std::make_unique<ExpressionStmt>(std::move(expr));
}

std::unique_ptr<Stmt> Parser::printStatement() {
  auto value = expression();
  consume(TokenType::SEMICOLON, "Expect ';' after value.");
  return std::make_unique<PrintStmt>(std::move(value));
}

std::unique_ptr<Expr> Parser::expression() { return addition(); }

std::unique_ptr<Expr> Parser::addition() {
  auto expr = multiplication();
  while (match({TokenType::PLUS, TokenType::MINUS})) {
    Token op = previous();
    auto right = multiplication();
    expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
  }
  return expr;
}

std::unique_ptr<Expr> Parser::multiplication() {
  auto expr = primary();
  while (match({TokenType::MULTI, TokenType::DIV})) {
    Token op = previous();
    auto right = primary();
    expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
  }
  return expr;
}

std::unique_ptr<Expr> Parser::primary() {
  if (match({TokenType::NUMBER})) {
    return std::make_unique<LiteralExpr>(std::stod(previous().value));
  }
  if (match({TokenType::IDENTIFIER})) {
    return std::make_unique<VariableExpr>(previous());
  }
  if (match({TokenType::LEFT_PAREN})) {
    auto expr = expression();
    consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
    return std::make_unique<GroupingExpr>(std::move(expr));
  }
  throw std::runtime_error("Expect expression.");
}

bool Parser::match(std::initializer_list<TokenType> types) {
  for (auto type : types) {
    if (check(type)) {
      advance();
      return true;
    }
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
    current++;
  return previous();
}

bool Parser::isAtEnd() { return peek().type == TokenType::END_OF_FILE; }

Token Parser::peek() { return tokens[current]; }

Token Parser::previous() { return tokens[current - 1]; }

Token Parser::consume(TokenType type, std::string message) {
  if (check(type))
    return advance();
  throw std::runtime_error(message);
}
