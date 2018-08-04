#ifndef CALCULATION_H
#define CALCULATION_H

#include <QtCore/QQueue>
#include <QtCore/QString>
#include "../ctl.h"

namespace Calculation{
    QString calculateExpr(QString& expr, CMap<QString, double>& doubleList);
    QString changeToPostfix(const QString& expr);
    QString calculatePostfix(const QString& expr, CMap<QString, double>& doubleList);
    bool chunking(const QString& expr, QString& chunk, int& start);
    void numberChunk(const QString& expr, QString& chunk, int& start);
    void symbolChunk(const QString& expr, QString& chunk, int& start);
    void specialChunk(const QString& expr, QString& chunk, int& start);
    int precedence(const QString& op);
    void processOp(const QString& op, CStack<QString>& stack, QString& result);
    void processOperand(const QString& operand, QString& result);
    void processOperator(const QString& _operator, CStack<QString>& stack, QString& result);
    void remainOperators(CStack<QString>& stack, QString& result);
    bool isOperand(const QString& expr);
    bool isInt(const double& num);
    bool isArithmetic(const QString& op);
}
#endif
