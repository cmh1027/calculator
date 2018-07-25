#include "operation.h"

namespace Operation{
    void plus(QStack<QString>& stack){
        double first, second;
        second = stack.top().toDouble();
        stack.pop();
        first = stack.top().toDouble();
        stack.pop();
        stack.push(doubleToString(first+second));
    }

    void minus(QStack<QString>& stack){
        double first, second;
        second = stack.top().toDouble();
        stack.pop();
        first = stack.top().toDouble();
        stack.pop();
        stack.push(doubleToString(first-second));
    }

    void mult(QStack<QString>& stack){
        double first, second;
        second = stack.top().toDouble();
        stack.pop();
        first = stack.top().toDouble();
        stack.pop();
        stack.push(doubleToString(first*second));
    }

    void divide(QStack<QString>& stack){
        double first, second;
        second = stack.top().toDouble();
        stack.pop();
        first = stack.top().toDouble();
        stack.pop();
        stack.push(doubleToString(first/second));
    }

    void sqrt(QStack<QString>& stack){
        double first;
        first = stack.top().toDouble();
        stack.pop();
        if(first < 0)
            stack.push(doubleToString(std::nan("")));
        else
            stack.push(doubleToString(std::pow(first, 1/2)));
    }

    void root(QStack<QString>& stack){
        double first, second;
        second = stack.top().toDouble();
        stack.pop();
        first = stack.top().toDouble();
        stack.pop();
        if(first < 0 && second - (int)second == 0 && (int)second % 2 == 0)
            stack.push(doubleToString(std::nan("")));
        else
            stack.push(doubleToString(std::pow(first, 1/second)));
    }

    void sqr(QStack<QString>& stack){
        double first;
        first = stack.top().toDouble();
        stack.pop();
        stack.push(doubleToString(std::pow(first, 2)));
    }

    void pow(QStack<QString>& stack){
        double first, second;
        second = stack.top().toDouble();
        stack.pop();
        first = stack.top().toDouble();
        stack.pop();
        stack.push(doubleToString(std::pow(first, second)));
    }

    void inv(QStack<QString>& stack){
        double first;
        first = stack.top().toDouble();
        stack.pop();
        stack.push(doubleToString(1/first));
    }

    void sin(QStack<QString>& stack){
        double first;
        first = stack.top().toDouble();
        stack.pop();
        stack.push(doubleToString(std::sin(first*Constant["pi"]/180)));
    }

    void cos(QStack<QString>& stack){
        double first;
        first = stack.top().toDouble();
        stack.pop();
        stack.push(doubleToString(std::cos(first*Constant["pi"]/180)));
    }

    void tan(QStack<QString>& stack){
        double first;
        first = stack.top().toDouble();
        stack.pop();
        stack.push(doubleToString(std::tan(first*Constant["pi"]/180)));
    }

    void asin(QStack<QString>& stack){
        double first;
        first = stack.top().toDouble();
        stack.pop();
        stack.push(doubleToString(std::asin(first)));
    }

    void acos(QStack<QString>& stack){
        double first;
        first = stack.top().toDouble();
        stack.pop();
        stack.push(doubleToString(std::acos(first)));
    }

    void atan(QStack<QString>& stack){
        double first;
        first = stack.top().toDouble();
        stack.pop();
        stack.push(doubleToString(std::atan(first)));
    }

    void sinh(QStack<QString>& stack){
        double first;
        first = stack.top().toDouble();
        stack.pop();
        stack.push(doubleToString(std::sinh(first)));
    }

    void cosh(QStack<QString>& stack){
        double first;
        first = stack.top().toDouble();
        stack.pop();
        stack.push(doubleToString(std::cosh(first)));
    }

    void tanh(QStack<QString>& stack){
        double first;
        first = stack.top().toDouble();
        stack.pop();
        stack.push(doubleToString(std::tanh(first)));
    }

    void log(QStack<QString>& stack){
        double first;
        first = stack.top().toDouble();
        stack.pop();
        stack.push(doubleToString(std::log10(first)));
    }

    void ln(QStack<QString>& stack){
        double first;
        first = stack.top().toDouble();
        stack.pop();
        stack.push(doubleToString(std::log(first)));
    }

    void mod(QStack<QString>& stack){
        double first, second;
        second = stack.top().toDouble();
        stack.pop();
        first = stack.top().toDouble();
        stack.pop();
        stack.push(doubleToString(std::fmod(first, second)));
    }

    void fac(QStack<QString>& stack){
        double first;
        first = stack.top().toDouble();
        stack.pop();
        stack.push(doubleToString(std::lgamma(first+1)));
    }

    void negate(QStack<QString>& stack){
        double first;
        first = stack.top().toDouble();
        stack.pop();
        stack.push(doubleToString(-1 * first));
    }

    void abs(QStack<QString>& stack){
        double first;
        first = stack.top().toDouble();
        stack.pop();
        stack.push(doubleToString(std::abs(first)));
    }
}
