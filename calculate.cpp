#include "calculate.h"
std::string doubleToString(const double &number){
    std::ostringstream strs;
    strs << number;
    std::string str = strs.str();
    return str;
}

void Operation::plus(QStack<QString>& stack){
    double first, second;
    second = stack.top().toDouble();
    stack.pop();
    first = stack.top().toDouble();
    stack.pop();
    stack.push(QString::fromStdString(doubleToString(first+second)));
}

void Operation::minus(QStack<QString>& stack){
    double first, second;
    second = stack.top().toDouble();
    stack.pop();
    first = stack.top().toDouble();
    stack.pop();
    stack.push(QString::fromStdString(doubleToString(first-second)));
}

void Operation::mult(QStack<QString>& stack){
    double first, second;
    second = stack.top().toDouble();
    stack.pop();
    first = stack.top().toDouble();
    stack.pop();
    stack.push(QString::fromStdString(doubleToString(first*second)));
}

void Operation::divide(QStack<QString>& stack){
    double first, second;
    second = stack.top().toDouble();
    stack.pop();
    first = stack.top().toDouble();
    stack.pop();
    stack.push(QString::fromStdString(doubleToString(first/second)));
}

void Operation::root(QStack<QString>& stack){
    double first, second;
    second = stack.top().toDouble();
    stack.pop();
    first = stack.top().toDouble();
    stack.pop();
    stack.push(QString::fromStdString(doubleToString(std::pow(first, 1/second))));
}

void Operation::pow(QStack<QString>& stack){
    double first, second;
    second = stack.top().toDouble();
    stack.pop();
    first = stack.top().toDouble();
    stack.pop();
    stack.push(QString::fromStdString(doubleToString(std::pow(first, second))));
}

void Operation::inv(QStack<QString>& stack){
    double first;
    first = stack.top().toDouble();
    stack.pop();
    stack.push(QString::fromStdString(doubleToString(1/first)));
}

void Operation::sin(QStack<QString>& stack){
    double first;
    first = stack.top().toDouble();
    stack.pop();
    stack.push(QString::fromStdString(doubleToString(std::sin(first*M_PI/180))));
}

void Operation::cos(QStack<QString>& stack){
    double first;
    first = stack.top().toDouble();
    stack.pop();
    stack.push(QString::fromStdString(doubleToString(std::cos(first*M_PI/180))));
}

void Operation::tan(QStack<QString>& stack){
    double first;
    first = stack.top().toDouble();
    stack.pop();
    stack.push(QString::fromStdString(doubleToString(std::tan(first*M_PI/180))));
}

void Operation::asin(QStack<QString>& stack){
    double first;
    first = stack.top().toDouble();
    stack.pop();
    stack.push(QString::fromStdString(doubleToString(std::asin(first))));
}

void Operation::acos(QStack<QString>& stack){
    double first;
    first = stack.top().toDouble();
    stack.pop();
    stack.push(QString::fromStdString(doubleToString(std::acos(first))));
}

void Operation::atan(QStack<QString>& stack){
    double first;
    first = stack.top().toDouble();
    stack.pop();
    stack.push(QString::fromStdString(doubleToString(std::atan(first))));
}

void Operation::sinh(QStack<QString>& stack){
    double first;
    first = stack.top().toDouble();
    stack.pop();
    stack.push(QString::fromStdString(doubleToString(std::sinh(first))));
}

void Operation::cosh(QStack<QString>& stack){
    double first;
    first = stack.top().toDouble();
    stack.pop();
    stack.push(QString::fromStdString(doubleToString(std::cosh(first))));
}

void Operation::tanh(QStack<QString>& stack){
    double first;
    first = stack.top().toDouble();
    stack.pop();
    stack.push(QString::fromStdString(doubleToString(std::tanh(first))));
}

void Operation::log(QStack<QString>& stack){
    double first;
    first = stack.top().toDouble();
    stack.pop();
    stack.push(QString::fromStdString(doubleToString(std::log(first))));
}

void Operation::mod(QStack<QString>& stack){
    double first, second;
    second = stack.top().toDouble();
    stack.pop();
    first = stack.top().toDouble();
    stack.pop();
    stack.push(QString::fromStdString(doubleToString(std::fmod(first, second))));
}

void Operation::fac(QStack<QString>& stack){
    double first;
    first = stack.top().toDouble();
    stack.pop();
    stack.push(QString::fromStdString(doubleToString(std::lgamma(first+1))));
}
