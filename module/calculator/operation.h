#ifndef OPERATION_H
#define OPERATION_H
#include "constant.h"
#include <QtCore/QStack>
#include <QtCore/QString>
#include <string>
#include <cmath>

using namespace Const;

namespace Operation{
    void plus(QStack<double>& stack);
    void minus(QStack<double>& stack);
    void mult(QStack<double>& stack);
    void divide(QStack<double>& stack);
    void sqrt(QStack<double>& stack);
    void root(QStack<double>& stack);
    void sqr(QStack<double>& stack);
    void cube(QStack<double>& stack);
    void pow(QStack<double>& stack);
    void inv(QStack<double>& stack);
    void negate(QStack<double>& stack);
    void sin(QStack<double>& stack);
    void cos(QStack<double>& stack);
    void tan(QStack<double>& stack);
    void asin(QStack<double>& stack);
    void acos(QStack<double>& stack);
    void atan(QStack<double>& stack);
    void sinh(QStack<double>& stack);
    void cosh(QStack<double>& stack);
    void tanh(QStack<double>& stack);
    void log(QStack<double>& stack);
    void ln(QStack<double>& stack);
    void mod(QStack<double>& stack);
    void fac(QStack<double>& stack);
    void abs(QStack<double>& stack);

}
#endif // OPERATION_H
