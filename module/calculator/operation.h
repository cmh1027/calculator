#ifndef OPERATION_H
#define OPERATION_H
#define _USE_MATH_DEFINES
#include <cmath>
#include <QtCore/QStack>
#include <QtCore/QString>
#include <sstream>
#include <string>

std::string doubleToString(const double &number);

namespace Operation{
    void plus(QStack<QString>& stack);
    void minus(QStack<QString>& stack);
    void mult(QStack<QString>& stack);
    void divide(QStack<QString>& stack);
    void sqrt(QStack<QString>& stack);
    void root(QStack<QString>& stack);
    void sqr(QStack<QString>& stack);
    void pow(QStack<QString>& stack);
    void inv(QStack<QString>& stack);
    void negate(QStack<QString>& stack);
    void sin(QStack<QString>& stack);
    void cos(QStack<QString>& stack);
    void tan(QStack<QString>& stack);
    void asin(QStack<QString>& stack);
    void acos(QStack<QString>& stack);
    void atan(QStack<QString>& stack);
    void sinh(QStack<QString>& stack);
    void cosh(QStack<QString>& stack);
    void tanh(QStack<QString>& stack);
    void log(QStack<QString>& stack);
    void mod(QStack<QString>& stack);
    void fac(QStack<QString>& stack);

}
#endif // OPERATION_H
