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
}

double Configuration::getConstant(const QString &str) const{
    return this->constants[str];
}

void Configuration::removeConstant(const QString &str){
    if(this->constants.contains(str))
        this->constants.remove(str);
}

const CMap<QString, Const::ConstObject>* Configuration::getConstantList(){
    return &constants;
}

bool Configuration::getRadian(){
    return this->radian;
}

void Configuration::setRadian(bool radian){
    this->radian = radian;
}

int Configuration::getPrecision(){
    return this->precision;
}

void Configuration::setPrecision(int precision){
    this->precision = precision;
}
