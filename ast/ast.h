#ifndef AST_H
#define AST_H

#include <memory>
#include <string>
#include <vector>

#include "../token/token.h"

class Expr {
   public:
    virtual ~Expr() = default;
};

class LiteralExpr : public Expr {
   public:
    double value;
    LiteralExpr(double value) : value(value) {}
};

class VariableExpr : public Expr {
   public:
    Token name;
    VariableExpr(Token name) : name(name) {}
};

class BinaryExpr : public Expr {
   public:
    std::unique_ptr<Expr> left;
    Token op;
    std::unique_ptr<Expr> right;

    BinaryExpr(std::unique_ptr<Expr> left, Token op,
               std::unique_ptr<Expr> right)
        : left(std::move(left)), op(op), right(std::move(right)) {}
};

class GroupingExpr : public Expr {
   public:
    std::unique_ptr<Expr> expression;
    GroupingExpr(std::unique_ptr<Expr> expression)
        : expression(std::move(expression)) {}
};

class Stmt {
   public:
    virtual ~Stmt() = default;
};

class VarStmt : public Stmt {
   public:
    Token name;
    std::unique_ptr<Expr> initializer;

    VarStmt(Token name, std::unique_ptr<Expr> initializer)
        : name(name), initializer(std::move(initializer)) {}
};

class PrintStmt : public Stmt {
   public:
    std::unique_ptr<Expr> expression;
    PrintStmt(std::unique_ptr<Expr> expression)
        : expression(std::move(expression)) {}
};

class ExpressionStmt : public Stmt {
   public:
    std::unique_ptr<Expr> expression;
    ExpressionStmt(std::unique_ptr<Expr> expression)
        : expression(std::move(expression)) {}
};

#endif
