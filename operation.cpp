#include "operation.h"
std::string doubleToString(const double &number){
    std::ostringstream strs;
    strs << number;
    std::string str = strs.str();
    return str;
}

namespace Operation{
    void plus(QStack<QString>& stack){
        double first, second;
        second = stack.top().toDouble();
        stack.pop();
        first = stack.top().toDouble();
        stack.pop();
        stack.push(QString::fromStdString(doubleToString(first+second)));
    }

    void minus(QStack<QString>& stack){
        double first, second;
        second = stack.top().toDouble();
        stack.pop();
        first = stack.top().toDouble();
        stack.pop();
        stack.push(QString::fromStdString(doubleToString(first-second)));
    }

    void mult(QStack<QString>& stack){
        double first, second;
        second = stack.top().toDouble();
        stack.pop();
        first = stack.top().toDouble();
        stack.pop();
        stack.push(QString::fromStdString(doubleToString(first*second)));
    }

    void divide(QStack<QString>& stack){
        double first, second;
        second = stack.top().toDouble();
        stack.pop();
        first = stack.top().toDouble();
        stack.pop();
        stack.push(QString::fromStdString(doubleToString(first/second)));
    }

    void sqrt(QStack<QString>& stack){
        double first;
        first = stack.top().toDouble();
        stack.pop();
        if(first < 0)
            stack.push(QString::fromStdString(doubleToString(std::nan(""))));
        else
            stack.push(QString::fromStdString(doubleToString(std::pow(first, 1/2))));
    }

    void root(QStack<QString>& stack){
        double first, second;
        second = stack.top().toDouble();
        stack.pop();
        first = stack.top().toDouble();
        stack.pop();
        if(first < 0 && second - (int)second == 0 && (int)second % 2 == 0)
            stack.push(QString::fromStdString(doubleToString(std::nan(""))));
        else
            stack.push(QString::fromStdString(doubleToString(std::pow(first, 1/second))));
    }

    void sqr(QStack<QString>& stack){
        double first;
        first = stack.top().toDouble();
        stack.pop();
        stack.push(QString::fromStdString(doubleToString(std::pow(first, 2))));
    }

    void pow(QStack<QString>& stack){
        double first, second;
        second = stack.top().toDouble();
        stack.pop();
        first = stack.top().toDouble();
        stack.pop();
        stack.push(QString::fromStdString(doubleToString(std::pow(first, second))));
    }

    void inv(QStack<QString>& stack){
        double first;
        first = stack.top().toDouble();
        stack.pop();
        stack.push(QString::fromStdString(doubleToString(1/first)));
    }

    void sin(QStack<QString>& stack){
        double first;
        first = stack.top().toDouble();
        stack.pop();
        stack.push(QString::fromStdString(doubleToString(std::sin(first*M_PI/180))));
    }

    void cos(QStack<QString>& stack){
        double first;
        first = stack.top().toDouble();
        stack.pop();
        stack.push(QString::fromStdString(doubleToString(std::cos(first*M_PI/180))));
    }

    void tan(QStack<QString>& stack){
        double first;
        first = stack.top().toDouble();
        stack.pop();
        stack.push(QString::fromStdString(doubleToString(std::tan(first*M_PI/180))));
    }

    void asin(QStack<QString>& stack){
        double first;
        first = stack.top().toDouble();
        stack.pop();
        stack.push(QString::fromStdString(doubleToString(std::asin(first))));
    }

    void acos(QStack<QString>& stack){
        double first;
        first = stack.top().toDouble();
        stack.pop();
        stack.push(QString::fromStdString(doubleToString(std::acos(first))));
    }

    void atan(QStack<QString>& stack){
        double first;
        first = stack.top().toDouble();
        stack.pop();
        stack.push(QString::fromStdString(doubleToString(std::atan(first))));
    }

    void sinh(QStack<QString>& stack){
        double first;
        first = stack.top().toDouble();
        stack.pop();
        stack.push(QString::fromStdString(doubleToString(std::sinh(first))));
    }

    void cosh(QStack<QString>& stack){
        double first;
        first = stack.top().toDouble();
        stack.pop();
        stack.push(QString::fromStdString(doubleToString(std::cosh(first))));
    }

    void tanh(QStack<QString>& stack){
        double first;
        first = stack.top().toDouble();
        stack.pop();
        stack.push(QString::fromStdString(doubleToString(std::tanh(first))));
    }

    void log(QStack<QString>& stack){
        double first;
        first = stack.top().toDouble();
        stack.pop();
        stack.push(QString::fromStdString(doubleToString(std::log(first))));
    }

    void mod(QStack<QString>& stack){
        double first, second;
        second = stack.top().toDouble();
        stack.pop();
        first = stack.top().toDouble();
        stack.pop();
        stack.push(QString::fromStdString(doubleToString(std::fmod(first, second))));
    }

    void fac(QStack<QString>& stack){
        double first;
        first = stack.top().toDouble();
        stack.pop();
        stack.push(QString::fromStdString(doubleToString(std::lgamma(first+1))));
    }

    void negate(QStack<QString>& stack){
        double first;
        first = stack.top().toDouble();
        stack.pop();
        stack.push(QString::fromStdString(doubleToString(-1 * first)));
    }
}
