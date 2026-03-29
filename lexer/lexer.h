#ifndef LEXER_H
#define LEXER_H

#include "../token/token.h"
#include <string>
#include <vector>

class Lexer {
public:
  Lexer(std::string source);
  std::vector<Token> scanTokens();

private:
  std::string source;
  std::vector<Token> tokens;
  int start = 0;
  int current = 0;
  int line = 1;

  bool isAtEnd();
  char advance();
  char peek();
  void scanToken();

  void number();
  void identifier();
  void addToken(TokenType type);
  void addToken(TokenType type, std::string lexeme);
};

#endif
