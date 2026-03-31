#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../ast/ast.h"

class Interpreter {
   public:
    void interpret(const std::vector<std::unique_ptr<Stmt>>& statements);

   private:
    std::map<std::string, double> environment;

    void execute(Stmt* stmt);
    void visitVarStmt(VarStmt* stmt);
    void visitPrintStmt(PrintStmt* stmt);
    void visitExpressionStmt(ExpressionStmt* stmt);

    double evaluate(Expr* expr);
    double visitLiteralExpr(LiteralExpr* expr);
    double visitVariableExpr(VariableExpr* expr);
    double visitBinaryExpr(BinaryExpr* expr);
    double visitGroupingExpr(GroupingExpr* expr);
};

#endif
