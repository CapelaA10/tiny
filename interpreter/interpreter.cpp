#include "interpreter.h"
#include <stdexcept>

void Interpreter::interpret(const std::vector<std::unique_ptr<Stmt>>& statements) {
    try {
        for (const auto& stmt : statements) {
            execute(stmt.get());
        }
    } catch (const std::runtime_error& error) {
        std::cerr << "Runtime Error: " << error.what() << std::endl;
    }
}

void Interpreter::execute(Stmt* stmt) {
    if (auto s = dynamic_cast<VarStmt*>(stmt)) {
        visitVarStmt(s);
    } else if (auto s = dynamic_cast<PrintStmt*>(stmt)) {
        visitPrintStmt(s);
    } else if (auto s = dynamic_cast<ExpressionStmt*>(stmt)) {
        visitExpressionStmt(s);
    } else {
        std::cerr << "Internal Error: Unknown Statement Type" << std::endl;
    }
}

void Interpreter::visitVarStmt(VarStmt* stmt) {
    double value = 0;
    if (stmt->initializer != nullptr) {
        value = evaluate(stmt->initializer.get());
    }
    environment[stmt->name.value] = value;
}

double Interpreter::visitVariableExpr(VariableExpr* expr) {
    if (environment.count(expr->name.value)) {
        return environment[expr->name.value];
    }
    throw std::runtime_error("Undefined variable '" + expr->name.value + "'.");
}

void Interpreter::visitPrintStmt(PrintStmt* stmt) {
    double value = evaluate(stmt->expression.get());
    std::cout << value << std::endl;
}

void Interpreter::visitExpressionStmt(ExpressionStmt* stmt) {
    evaluate(stmt->expression.get());
}

double Interpreter::evaluate(Expr* expr) {
    if (auto e = dynamic_cast<LiteralExpr*>(expr)) return visitLiteralExpr(e);
    if (auto e = dynamic_cast<VariableExpr*>(expr)) return visitVariableExpr(e);
    if (auto e = dynamic_cast<BinaryExpr*>(expr)) return visitBinaryExpr(e);
    if (auto e = dynamic_cast<GroupingExpr*>(expr)) return visitGroupingExpr(e);
    throw std::runtime_error("Unknown expression type.");
}

double Interpreter::visitLiteralExpr(LiteralExpr* expr) {
    return expr->value;
}

double Interpreter::visitBinaryExpr(BinaryExpr* expr) {
    double left = evaluate(expr->left.get());
    double right = evaluate(expr->right.get());

    switch (expr->op.type) {
        case TokenType::PLUS:  return left + right;
        case TokenType::MINUS: return left - right;
        case TokenType::MULTI: return left * right;
        case TokenType::DIV:
            if (right == 0) throw std::runtime_error("Division by zero.");
            return left / right;
        default: return 0;
    }
}

double Interpreter::visitGroupingExpr(GroupingExpr* expr) {
    return evaluate(expr->expression.get());
}