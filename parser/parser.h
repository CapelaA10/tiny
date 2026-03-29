#ifndef PARSER_H
#define PARSER_H

#include "../ast/ast.h"
#include "../token/token.h"
#include <memory>
#include <stdexcept>
#include <vector>

class Parser {
public:
  Parser(const std::vector<Token> &tokens);

  std::vector<std::unique_ptr<Stmt>> parseProgram();

private:
  std::vector<Token> tokens;
  int current = 0;

  std::unique_ptr<Stmt> declaration();
  std::unique_ptr<Stmt> varDeclaration();
  std::unique_ptr<Stmt> statement();
  std::unique_ptr<Stmt> printStatement();

  std::unique_ptr<Expr> expression();
  std::unique_ptr<Expr> addition();
  std::unique_ptr<Expr> multiplication();
  std::unique_ptr<Expr> primary();

  bool match(std::initializer_list<TokenType> types);
  bool check(TokenType type);
  Token advance();
  bool isAtEnd();
  Token peek();
  Token previous();
  Token consume(TokenType type, std::string message);
};

#endif
