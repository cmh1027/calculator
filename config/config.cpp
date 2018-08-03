#include "config.h"
#include "../module/calculator/constant.h"
#include "../template/mainwindow.h"
#include "../template/content/config/config_content.h"

Configuration::Configuration(MainWindow* window) :
    constants({{"{pi}", Const::PI}, {"{e}", Const::E}}), mainWindow(window),
    radian(false), precision(-1)
{

}

Configuration::~Configuration(){

}

void Configuration::addConstant(const QString &str, const double &num){
    this->constants[str] = num;
}

double Configuration::getConstant(const QString &str) const{
    return this->constants[str];
}

void Configuration::removeConstant(const QString &str){
    if(this->constants.contains(str))
        this->constants.remove(str);
}

const QMap<QString, double>* Configuration::getConstantList(){
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
