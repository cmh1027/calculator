#ifndef CALCULATE_H
#define CALCULATE_H

#include <cmath>
#include <stack>
#include <QtCore/QString>
#include <QtCore/QPair>

double calculate(const QString& expr);
QString changeToPostfix(const QString& expr);
double calculatePostfix(const QString& expr);
bool isSpecialOperator(const QString& expr);
QPair<QString, QString> splitOperator(const QString& expr);
int nextIndex(const QString& expr, int start);
int precedence(const QString& op);
void processOp(const QPair<QString, QString>& ops, std::stack<QString>& stack, QString& result);
void processOp(const QString& op, std::stack<QString>& stack, QString& result);
void processOperand(const QString& operand, QString& result);
void processOperator(const QString& _operator, std::stack<QString>& stack, QString& result);

#endif