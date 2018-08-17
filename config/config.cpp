#include <QString>
#include "config.h"
#include "../module/mathcontent/constant.h"
#include "../template/mainwindow.h"
#include "../template/content/config/config_content.h"
namespace Configuration{
    Configuration::Configuration(MainWindow* window) :
        constants({{"{pi}", new Const::ConstObject(Const::PI, true, false, "Pi")},
                   {"{e}", new Const::ConstObject(Const::E, true, false, "Euler's number")}}),
        operateFuncs({
            {Operator::Normal::plus, Operation::OperationObject(Operation::plus, "Plus", Operation::Arithmetic, true)},
            {Operator::Normal::minus, Operation::OperationObject(Operation::minus, "Minus", Operation::Arithmetic, true)},
            {Operator::Normal::mult, Operation::OperationObject(Operation::mult, "Multiply", Operation::Arithmetic, true)},
            {Operator::Normal::divide, Operation::OperationObject(Operation::divide, "Divide", Operation::Arithmetic, true)},
            {Operator::Normal::altMult, Operation::OperationObject(Operation::mult, "Multiply", Operation::Arithmetic, true)},
            {Operator::Normal::altDivide, Operation::OperationObject(Operation::divide, "Divide", Operation::Arithmetic, true)},
            {Operator::Special::sqrt, Operation::OperationObject(Operation::sqrt, "Square root", Operation::Unary, true)},
            {Operator::Special::root, Operation::OperationObject(Operation::root, "Root", Operation::Binary, true)},
            {Operator::Special::sqr, Operation::OperationObject(Operation::sqr, "Square", Operation::Unary, true)},
            {Operator::Special::cube, Operation::OperationObject(Operation::cube, "Cube", Operation::Unary, true)},
            {Operator::Special::pow, Operation::OperationObject(Operation::pow, "Power", Operation::Binary, true)},
            {Operator::Special::negate, Operation::OperationObject(Operation::negate, "Negate", Operation::Unary, true)},
            {Operator::Special::inv, Operation::OperationObject(Operation::inv, "Inverse", Operation::Unary, true)},
            {Operator::Special::sin, Operation::OperationObject(Operation::sin, "Sine", Operation::Unary, true)},
            {Operator::Special::cos, Operation::OperationObject(Operation::cos, "Cosine", Operation::Unary, true)},
            {Operator::Special::tan, Operation::OperationObject(Operation::tan, "Tangent", Operation::Unary, true)},
            {Operator::Special::asin, Operation::OperationObject(Operation::asin, "Arcsine", Operation::Unary, true)},
            {Operator::Special::acos, Operation::OperationObject(Operation::acos, "Arccosine", Operation::Unary, true)},
            {Operator::Special::atan, Operation::OperationObject(Operation::atan, "Arctangent", Operation::Unary, true)},
            {Operator::Special::log, Operation::OperationObject(Operation::log, "Logarithmic", Operation::Unary, true)},
            {Operator::Special::ln, Operation::OperationObject(Operation::ln, "Natural logarithmic", Operation::Unary, true)},
            {Operator::Special::mod, Operation::OperationObject(Operation::mod, "Mod", Operation::Binary, true)},
            {Operator::Special::abs, Operation::OperationObject(Operation::abs, "Absolute value", Operation::Unary, true)},
            {Operator::Special::fac, Operation::OperationObject(Operation::fac, "Factorial", Operation::Unary, true)},
            {Operator::Special::sinh, Operation::OperationObject(Operation::sinh, "Hyperbolic sine", Operation::Unary, true)},
            {Operator::Special::cosh, Operation::OperationObject(Operation::cosh, "Hyperbolic cosine", Operation::Unary, true)},
            {Operator::Special::tanh, Operation::OperationObject(Operation::tanh, "Hyperbolic tangent", Operation::Unary, true)}
        }),
        mainWindow(window), radian(false), precision(-1)
    {

    }

    Configuration::~Configuration(){
        for(auto it = this->constants.begin(); it != this->constants.end(); ++it){
            if(!(*it)->isTemp())
                delete (*it);
        }
    }

    void Configuration::addConstant(const QString &str, Const::ConstObject* num){
        if(!this->constants.contains(str))
            this->constants[str] = num;
        this->mainWindow->addConstant(str, num);
        this->mainWindow->refreshAllContents();
    }


    double Configuration::getConstant(const QString &str) const{
        return *this->constants.value(str);
    }

    void Configuration::removeConstant(const QString &str){
        if(this->constants.contains(str)){
            this->constants.remove(str);
        }
        this->mainWindow->removeConstant(str);
        this->mainWindow->refreshAllContents();
    }

    void Configuration::addFunction(const QString &str, Operation::OperationObject& num){
        if(!this->operateFuncs.contains(str))
            this->operateFuncs[str] = num;
        this->refreshAllContents();
    }

    void Configuration::removeFunction(const QString &str){
        if(this->operateFuncs.contains(str))
            this->operateFuncs.remove(str);
        this->mainWindow->refreshAllContents();
    }

    CMap<QString, Const::ConstObject*>& Configuration::getConstantList(){
        return this->constants;
    }
    CMap<QString, Operation::OperationObject>& Configuration::getFuncList(){
        return this->operateFuncs;
    }

    bool Configuration::getRadian(){
        return this->radian;
    }

    void Configuration::setRadian(const bool& radian){
        if(this->radian != radian){
            this->radian = radian;
            this->mainWindow->degreeUnitChanged();
        }
    }

    int Configuration::getPrecision(){
        return this->precision;
    }

    void Configuration::setPrecision(const int& precision){
        if(this->precision != precision){
            this->precision = precision;
            this->mainWindow->precisionChanged();
        }
    }

    void Configuration::refreshAllContents(){
        this->mainWindow->refreshAllContents();
    }
}
