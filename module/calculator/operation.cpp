#include "operation.h"
namespace Operation{
    void plus(QStack<double>& stack){
        double first, second;
        second = stack.top();
        stack.pop();
        first = stack.top();
        stack.pop();
        stack.push(first+second);
    }

    void minus(QStack<double>& stack){
        double first, second;
        second = stack.top();
        stack.pop();
        first = stack.top();
        stack.pop();
        stack.push(first-second);
    }

    void mult(QStack<double>& stack){
        double first, second;
        second = stack.top();
        stack.pop();
        first = stack.top();
        stack.pop();
        stack.push(first*second);
    }

    void divide(QStack<double>& stack){
        double first, second;
        second = stack.top();
        stack.pop();
        first = stack.top();
        stack.pop();
        stack.push(first/second);
    }

    void sqrt(QStack<double>& stack){
        double first;
        first = stack.top();
        stack.pop();
        if(first < 0)
            stack.push(std::nan(""));
        else
            stack.push(std::sqrt(first));
    }

    void root(QStack<double>& stack){
        double first, second;
        second = stack.top();
        stack.pop();
        first = stack.top();
        stack.pop();
        if(first < 0 && second - (int)second == 0 && (int)second % 2 == 0)
            stack.push(std::nan(""));
        else
            stack.push(std::pow(first, 1/second));
    }

    void sqr(QStack<double>& stack){
        double first;
        first = stack.top();
        stack.pop();
        stack.push(std::pow(first, 2));
    }

    void cube(QStack<double>& stack){
        double first;
        first = stack.top();
        stack.pop();
        stack.push(std::pow(first, 3));
    }

    void pow(QStack<double>& stack){
        double first, second;
        second = stack.top();
        stack.pop();
        first = stack.top();
        stack.pop();
        stack.push(std::pow(first, second));
    }

    void inv(QStack<double>& stack){
        double first;
        first = stack.top();
        stack.pop();
        stack.push(1/first);
    }

    void sin(QStack<double>& stack){
        double first;
        first = stack.top();
        stack.pop();
        stack.push(std::sin(first*Constant["pi"]/180));
    }

    void cos(QStack<double>& stack){
        double first;
        first = stack.top();
        stack.pop();
        stack.push(std::cos(first*Constant["pi"]/180));
    }

    void tan(QStack<double>& stack){
        double first;
        first = stack.top();
        stack.pop();
        stack.push(std::tan(first*Constant["pi"]/180));
    }

    void asin(QStack<double>& stack){
        double first;
        first = stack.top();
        stack.pop();
        stack.push(std::asin(first));
    }

    void acos(QStack<double>& stack){
        double first;
        first = stack.top();
        stack.pop();
        stack.push(std::acos(first));
    }

    void atan(QStack<double>& stack){
        double first;
        first = stack.top();
        stack.pop();
        stack.push(std::atan(first));
    }

    void sinh(QStack<double>& stack){
        double first;
        first = stack.top();
        stack.pop();
        stack.push(std::sinh(first));
    }

    void cosh(QStack<double>& stack){
        double first;
        first = stack.top();
        stack.pop();
        stack.push(std::cosh(first));
    }

    void tanh(QStack<double>& stack){
        double first;
        first = stack.top();
        stack.pop();
        stack.push(std::tanh(first));
    }

    void log(QStack<double>& stack){
        double first;
        first = stack.top();
        stack.pop();
        stack.push(std::log10(first));
    }

    void ln(QStack<double>& stack){
        double first;
        first = stack.top();
        stack.pop();
        stack.push(std::log(first));
    }

    void mod(QStack<double>& stack){
        double first, second;
        second = stack.top();
        stack.pop();
        first = stack.top();
        stack.pop();
        stack.push(std::fmod(first, second));
    }

    void fac(QStack<double>& stack){
        double first;
        first = stack.top();
        stack.pop();
        stack.push(std::tgamma(first+1));
    }

    void negate(QStack<double>& stack){
        double first;
        first = stack.top();
        stack.pop();
        stack.push(-1 * first);
    }

    void abs(QStack<double>& stack){
        double first;
        first = stack.top();
        stack.pop();
        stack.push(std::abs(first));
    }
}
