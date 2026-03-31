#include "lexer.h"

#include <iostream>
#include <string>
#include <vector>

#include "../token/token.h"

Lexer::Lexer(std::string source) : source(source) {}

std::vector<Token> Lexer::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }
    tokens.push_back(Token{TokenType::END_OF_FILE, ""});
    return tokens;
}

bool Lexer::isAtEnd() { return current == source.size(); }

void Lexer::scanToken() {
    char c = advance();
    switch (c) {
        case '(':
            addToken(TokenType::LEFT_PAREN);
            break;
        case ')':
            addToken(TokenType::RIGHT_PAREN);
            break;
        case '+':
            addToken(TokenType::PLUS);
            break;
        case '-':
            addToken(TokenType::MINUS);
            break;
        case '*':
            addToken(TokenType::MULTI);
            break;
        case '/':
            addToken(TokenType::DIV);
            break;
        case '=':
            addToken(TokenType::EQUALS);
            break;
        case ';':
            addToken(TokenType::SEMICOLON);
            break;
        case '\n':
            line++;
            break;

        case ' ':
        case '\r':
        case '\t':
            break;

        default:
            if (isdigit(c)) {
                number();
            } else if (isalpha(c)) {
                identifier();
            } else {
                std::cout << "Unexpected symbol " << c << " at line " << line
                          << std::endl;
            }
            break;
    }
}

char Lexer::advance() { return source[current++]; }

char Lexer::peek() {
    if (isAtEnd()) {
        return '\0';
    }

    return source[current];
}

void Lexer::number() {
    while (isdigit(peek())) advance();

    if (peek() == '.' && isdigit(source[current + 1])) {
        advance();
        while (isdigit(peek())) advance();
    }

    addToken(TokenType::NUMBER);
}

void Lexer::identifier() {
    while (isalnum(peek())) advance();

    std::string text = source.substr(start, current - start);

    TokenType type = TokenType::IDENTIFIER;
    if (text == "let") type = TokenType::LET;
    if (text == "print") type = TokenType::PRINT;

    addToken(type);
}

void Lexer::addToken(TokenType type) {
    std::string text = source.substr(start, current - start);
    tokens.push_back(Token{type, text});
}
