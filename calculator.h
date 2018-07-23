#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QtCore/QQueue>
#include <QtCore/QMap>
#include <QtCore/QStack>
#include <QtCore/QString>
#include <iostream>
#include "calculate.h"

namespace Operator{
    namespace Normal{
        const QString Plus = "+";
        const QString Minus = "-";
        const QString Mult = "×";
        const QString Divide = "÷";
        const QString LeftBracket = "(";
        const QString RightBracket = ")";
    }
    namespace Special{
        const QString Root = "root";
        const QString Pow = "pow";
        const QString Inv = "inv";
        const QString Sin = "sin";
        const QString Cos = "cos";
        const QString Tan = "tan";
        const QString Asin = "asin";
        const QString Acos = "acos";
        const QString Atan = "atan";
        const QString Log = "log";
        const QString Mod = "mod";
        const QString Fac = "fac";
        const QString sinh = "sinh";
        const QString cosh = "cosh";
        const QString tanh = "tanh";
    }
    extern const QMap<QString, void(*)(QStack<QString>& stack)> operateFuncs;
}

QString calculateExpr(const QString& expr);
QString changeToPostfix(const QString& expr);
QString calculatePostfix(const QString& expr);
bool isUnarySpecial(const QString& expr);
QQueue<QString> splitOperator(const QString& expr);
int nextIndex(const QString& expr, int start, const QString& delimiter);
bool chunking(const QString& expr, QString& chunk, const QString& delimiter, int& start, int& end);
int precedence(const QString& op);
void processOp(QQueue<QString>&& ops, QString& result);
void processOp(const QString& op, QStack<QString>& stack, QString& result);
void processOperand(const QString& operand, QString& result);
void processOperator(const QString& _operator, QStack<QString>& stack, QString& result);
void remainOperators(QStack<QString>& stack, QString& result);
bool isOperand(const QString& expr);

#endif
