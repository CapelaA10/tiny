# TinySF

A small, self-contained interpreted language engine built as a learning challenge. The goal is to keep the interpreter minimal while still supporting:

- variable declaration
- basic arithmetic (add, subtract, multiply, divide)
- expression evaluation
- simple file-based input

This repository is not a production compiler — it’s a compact sandbox for understanding the full language pipeline (lexer, parser, AST, interpreter).

## Getting started

1. Build the interpreter:

   ```bash
   make
   ```

2. Run the example script:

   ```bash
   ./tiny test/test.ty
   ```

3. Edit `test/test.ty` or create your own `.ty` file to explore variables and math.

## Why this exists

Tiny is a programming exercise: keep the implementation readable, avoid advanced features, and get hands-on experience implementing the three core pieces of a language:

- lexing tokens from source text
- parsing tokens into an AST
- evaluating AST nodes with an interpreter