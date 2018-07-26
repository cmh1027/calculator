#ifndef OPERATOR_H
#define OPERATOR_H
#include <QString>
#include <QStack>
#include <QMap>
#include "operation.h"

namespace Operator{
    namespace Normal{
        const QString plus = "+";
        const QString minus = "-";
        const QString mult = "×";
        const QString divide = "÷";
        const QString leftBracket = "(";
        const QString rightBracket = ")";
        const QString altMult = "*";
        const QString altDivide = "/";
    }
    namespace Special{
        const QString sqrt = "sqrt";
        const QString sqr = "sqr";
        const QString cube = "cube";
        const QString root = "root";
        const QString pow = "pow";
        const QString inv = "inv";
        const QString sin = "sin";
        const QString cos = "cos";
        const QString tan = "tan";
        const QString asin = "asin";
        const QString acos = "acos";
        const QString atan = "atan";
        const QString log = "log";
        const QString ln = "ln";
        const QString mod = "mod";
        const QString fac = "fac";
        const QString sinh = "sinh";
        const QString cosh = "cosh";
        const QString tanh = "tanh";
        const QString negate = "negate";
        const QString abs = "abs";
    }
    extern const QMap<QString, void(*)(QStack<double>& stack)> operateFuncs;
}
#endif // OPERATOR_H
