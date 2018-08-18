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
            {Operator::Normal::plus, new Operation::OperationObject(Operation::plus, "Plus", Operation::Arithmetic, true)},
            {Operator::Normal::minus, new Operation::OperationObject(Operation::minus, "Minus", Operation::Arithmetic, true)},
            {Operator::Normal::mult, new Operation::OperationObject(Operation::mult, "Multiply", Operation::Arithmetic, true)},
            {Operator::Normal::divide, new Operation::OperationObject(Operation::divide, "Divide", Operation::Arithmetic, true)},
            {Operator::Normal::altMult,new Operation::OperationObject(Operation::mult, "Multiply", Operation::Arithmetic, true)},
            {Operator::Normal::altDivide, new Operation::OperationObject(Operation::divide, "Divide", Operation::Arithmetic, true)},
            {Operator::Special::sqrt, new Operation::OperationObject(Operation::sqrt, "Square root", Operation::Unary, true)},
            {Operator::Special::root, new Operation::OperationObject(Operation::root, "Root", Operation::Binary, true)},
            {Operator::Special::sqr, new Operation::OperationObject(Operation::sqr, "Square", Operation::Unary, true)},
            {Operator::Special::cube, new Operation::OperationObject(Operation::cube, "Cube", Operation::Unary, true)},
            {Operator::Special::pow, new Operation::OperationObject(Operation::pow, "Power", Operation::Binary, true)},
            {Operator::Special::negate, new Operation::OperationObject(Operation::negate, "Negate", Operation::Unary, true)},
            {Operator::Special::inv, new Operation::OperationObject(Operation::inv, "Inverse", Operation::Unary, true)},
            {Operator::Special::sin, new Operation::OperationObject(Operation::sin, "Sine", Operation::Unary, true)},
            {Operator::Special::cos, new Operation::OperationObject(Operation::cos, "Cosine", Operation::Unary, true)},
            {Operator::Special::tan, new Operation::OperationObject(Operation::tan, "Tangent", Operation::Unary, true)},
            {Operator::Special::asin, new Operation::OperationObject(Operation::asin, "Arcsine", Operation::Unary, true)},
            {Operator::Special::acos, new Operation::OperationObject(Operation::acos, "Arccosine", Operation::Unary, true)},
            {Operator::Special::atan, new Operation::OperationObject(Operation::atan, "Arctangent", Operation::Unary, true)},
            {Operator::Special::log, new Operation::OperationObject(Operation::log, "Logarithmic", Operation::Unary, true)},
            {Operator::Special::ln, new Operation::OperationObject(Operation::ln, "Natural logarithmic", Operation::Unary, true)},
            {Operator::Special::mod, new Operation::OperationObject(Operation::mod, "Mod", Operation::Binary, true)},
            {Operator::Special::abs, new Operation::OperationObject(Operation::abs, "Absolute value", Operation::Unary, true)},
            {Operator::Special::fac, new Operation::OperationObject(Operation::fac, "Factorial", Operation::Unary, true)},
            {Operator::Special::sinh, new Operation::OperationObject(Operation::sinh, "Hyperbolic sine", Operation::Unary, true)},
            {Operator::Special::cosh, new Operation::OperationObject(Operation::cosh, "Hyperbolic cosine", Operation::Unary, true)},
            {Operator::Special::tanh, new Operation::OperationObject(Operation::tanh, "Hyperbolic tangent", Operation::Unary, true)}
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

    void Configuration::addConstant(const QString &key, Const::ConstObject* num){
        if(!this->constants.contains(key))
            this->constants[key] = num;
        this->mainWindow->addConstant(key, num);
        this->mainWindow->refreshAllContents();
    }


    double Configuration::getConstant(const QString &key) const{
        return *this->constants.value(key);
    }

    void Configuration::removeConstant(const QString &key){
        if(this->constants.contains(key)){
            this->constants.remove(key);
        }
        this->mainWindow->removeConstant(key);
        this->mainWindow->refreshAllContents();
    }

    void Configuration::addFunction(const QString &key, Operation::OperationObject* func){
        if(!this->operateFuncs.contains(key))
            this->operateFuncs[key] = func;
        this->refreshAllContents();
    }

    void Configuration::removeFunction(const QString &key){
        if(this->operateFuncs.contains(key))
            this->operateFuncs.remove(key);
        this->mainWindow->refreshAllContents();
    }

    CMap<QString, Const::ConstObject*>& Configuration::getConstantList(){
        return this->constants;
    }
    CMap<QString, Operation::OperationObject*>& Configuration::getFuncList(){
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
