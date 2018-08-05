#include "operation.h"

namespace Operation{
    OperationObject::OperationObject(const funcType& function, const QString& des, const bool& flag) :
        DataObject(des, flag), func(function)
    {}

    void OperationObject::operator()(CStack<double>& stack){
        func(stack);
    }

    void plus(CStack<double>& stack){
        double first, second;
        second = stack.pop();
        first = stack.pop();
        stack.push(first+second);
    }

    void minus(CStack<double>& stack){
        double first, second;
        second = stack.pop();
        first = stack.pop();
        stack.push(first-second);
    }

    void mult(CStack<double>& stack){
        double first, second;
        second = stack.pop();
        first = stack.pop();
        stack.push(first*second);
    }

    void divide(CStack<double>& stack){
        double first, second;
        second = stack.pop();
        first = stack.pop();
        stack.push(first/second);
    }

    void sqrt(CStack<double>& stack){
        double first;
        first = stack.pop();
        if(first < 0)
            stack.push(std::nan(""));
        else
            stack.push(std::sqrt(first));
    }

    void root(CStack<double>& stack){
        double first, second;
        second = stack.pop();
        first = stack.pop();
        if(first < 0 && second - (int)second == 0 && (int)second % 2 == 0)
            stack.push(std::nan(""));
        else
            stack.push(std::pow(first, 1/second));
    }

    void sqr(CStack<double>& stack){
        double first;
        first = stack.pop();
        stack.push(std::pow(first, 2));
    }

    void cube(CStack<double>& stack){
        double first;
        first = stack.pop();
        stack.push(std::pow(first, 3));
    }

    void pow(CStack<double>& stack){
        double first, second;
        second = stack.pop();
        first = stack.pop();
        stack.push(std::pow(first, second));
    }

    void inv(CStack<double>& stack){
        double first;
        first = stack.pop();
        stack.push(1/first);
    }

    void sin(CStack<double>& stack){
        double first;
        first = stack.pop();
        stack.push(std::sin(first));
    }

    void cos(CStack<double>& stack){
        double first;
        first = stack.pop();
        stack.push(std::cos(first));
    }

    void tan(CStack<double>& stack){
        double first;
        first = stack.pop();
        stack.push(std::tan(first));
    }

    void asin(CStack<double>& stack){
        double first;
        first = stack.pop();
        stack.push(std::asin(first));
    }

    void acos(CStack<double>& stack){
        double first;
        first = stack.pop();
        stack.push(std::acos(first));
    }

    void atan(CStack<double>& stack){
        double first;
        first = stack.pop();
        stack.push(std::atan(first));
    }

    void sinh(CStack<double>& stack){
        double first;
        first = stack.pop();
        stack.push(std::sinh(first));
    }

    void cosh(CStack<double>& stack){
        double first;
        first = stack.pop();
        stack.push(std::cosh(first));
    }

    void tanh(CStack<double>& stack){
        double first;
        first = stack.pop();
        stack.push(std::tanh(first));
    }

    void log(CStack<double>& stack){
        double first;
        first = stack.pop();
        stack.push(std::log10(first));
    }

    void ln(CStack<double>& stack){
        double first;
        first = stack.pop();
        stack.push(std::log(first));
    }

    void mod(CStack<double>& stack){
        double first, second;
        second = stack.pop();
        first = stack.pop();
        stack.push(std::fmod(first, second));
    }

    void fac(CStack<double>& stack){
        double first;
        first = stack.pop();
        stack.push(std::tgamma(first+1));
    }

    void negate(CStack<double>& stack){
        double first;
        first = stack.pop();
        stack.push(-1 * first);
    }

    void abs(CStack<double>& stack){
        double first;
        first = stack.pop();
        stack.push(std::abs(first));
    }
}
