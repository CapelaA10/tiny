#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType {
  LET,         // 'let'
  IDENTIFIER,  // variable names
  NUMBER,      // '123'
  PLUS,        // '+'
  MINUS,       // '-'
  MULTI,       // '*'
  DIV,         // '/'
  EQUALS,      // '='
  PRINT,       // 'print'
  SEMICOLON,   // ';'
  LEFT_PAREN,  // '('
  RIGHT_PAREN, // ')'
  END_OF_FILE  // To know when to stop
};

struct Token {
  TokenType type;
  std::string value;
  double number;

  void print();
};

#endif
