#include "operation.h"
#include "calculation.h"

namespace Operation{
    namespace Unknown{
        const QString X = "𝒙";
        const QString Y = "𝒚";
    }

    OperationObject::OperationObject(const funcType& function, const QString& des, const Arity& t,
                                     const bool& defaultFlag) :
        DataObject(des, defaultFlag, false), func(function), type(t)
    {}

    OperationObject::OperationObject(const QString& function, const QString& des, const Arity& t,
                                     const bool& defaultFlag) :
        DataObject(des, defaultFlag, false), func(nullptr), expression(function), type(t)
    {}


    void OperationObject::call(CStack<double>& stack, CMap<QString, Const::ConstObject*>& doubleList){
        if(this->func != nullptr)
            this->func(stack);
        else{
            int num1 = 0;
            int num2 = 0;
            double x;
            double y;
            QString &&key = "{temp%1}";
            QString replaced = this->expression;
            while(doubleList.contains(key.arg(num1)))
                ++num1;
            while(doubleList.contains(key.arg(num2)) || num1 == num2)
                ++num2;
            if(this->type == Arity::Unary){
                x = stack.pop();
                doubleList[key.arg(num1)] = new Const::ConstObject(x);
                replaced.replace(Operation::Unknown::X, key.arg(num1));
                stack.push(Calculation::calculatePostfix(Calculation::changeToPostfix(replaced), doubleList));
                doubleList.remove(key.arg(num1));
            }
            else if(this->type == Arity::Binary){
                y = stack.pop();
                doubleList[key.arg(num1)] = new Const::ConstObject(y);
                x = stack.pop();
                doubleList[key.arg(num2)] = new Const::ConstObject(x);
                replaced.replace(Operation::Unknown::X, key.arg(num2)).replace(Operation::Unknown::Y, key.arg(num1));
                stack.push(Calculation::calculatePostfix(Calculation::changeToPostfix(replaced), doubleList));
                doubleList.remove(key.arg(num1));
                doubleList.remove(key.arg(num2));
            }
        }
    }

    void OperationObject::operator()(CStack<double>& stack, CMap<QString, Const::ConstObject*>& doubleList){
        this->call(stack, doubleList);
    }

    void OperationObject::setExpr(const QString& expr){
        this->expression = expr;
    }

    void OperationObject::setArity(Arity type){
        this->type = type;
    }

    QString OperationObject::getExpr() const{
        return this->expression;
    }

    Arity OperationObject::getArity() const{
        return this->type;
    }

    QString OperationObject::getArityString() const{
        switch(this->type){
            case Arity::Arithmetic:
                return "Arithmetic";
            case Arity::Unary:
                return "Unary";
            case Arity::Binary:
                return "Binary";
            default:
                return "";
        }
    }

    QString OperationObject::funcShape(const QString& name) const{
        switch(this->type){
            case Arity::Arithmetic:
                return QString("%1 %2 %3").arg(Operation::Unknown::X).arg(name).arg(Operation::Unknown::Y);
            case Arity::Unary:
                return QString("%1(%2)").arg(name).arg(Operation::Unknown::X);
            case Arity::Binary:
                return QString("%1 %2 %3").arg(Operation::Unknown::X).arg(name).arg(Operation::Unknown::Y);
            default:
                return "";
        }
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
