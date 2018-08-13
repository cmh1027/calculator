#include <QString>
#include "config.h"
#include "../module/calculator/constant.h"
#include "../template/mainwindow.h"
#include "../template/content/config/configcontent.h"
Configuration::Configuration(MainWindow* window) :
    constants({{"{pi}", Const::ConstObject(Const::PI, "Pi")},
               {"{e}", Const::ConstObject(Const::E, "Euler's number")}}),
    mainWindow(window), radian(false), precision(-1)
{

}

void Configuration::addConstant(const QString &str, const Const::ConstObject& num){
    this->constants[str] = num;
    this->mainWindow->addConstant(str, num);
}

double Configuration::getConstant(const QString &str) const{
    return this->constants[str];
}

void Configuration::removeConstant(const QString &str){
    if(this->constants.contains(str)){
        this->constants.remove(str);
        this->mainWindow->removeConstant(str);
    }
}

const CMap<QString, Const::ConstObject>* Configuration::getConstantList(){
    return &constants;
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
