#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "ast/ast.h"
#include "interpreter/interpreter.h"
#include "lexer/lexer.h"
#include "parser/parser.h"

std::string readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << path << std::endl;
        exit(1);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: ./tiny [script.tiny]" << std::endl;
        return 0;
    }

    std::string sourceCode = readFile(argv[1]);
    Lexer lexer(sourceCode);
    std::vector<Token> tokens = lexer.scanTokens();
    Parser parser(tokens);
    std::vector<std::unique_ptr<Stmt>> program;

    try {
        program = parser.parseProgram();
    } catch (const std::exception& e) {
        return 1;
    }

    if (!program.empty()) {
        Interpreter interpreter;
        interpreter.interpret(program);
    }

    return 0;
}
