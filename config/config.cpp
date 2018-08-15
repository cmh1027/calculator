#include <QString>
#include "config.h"
#include "../module/mathcontent/constant.h"
#include "../template/mainwindow.h"
#include "../template/content/config/configcontent.h"
Configuration::Configuration(MainWindow* window) :
    constants({{"{pi}", new Const::ConstObject(Const::PI, true, "Pi")},
               {"{e}", new Const::ConstObject(Const::E, true, "Euler's number")}}),
    mainWindow(window), radian(false), precision(-1)
{

}

Configuration::~Configuration(){
    for(auto it = this->constants.begin(); it != this->constants.end(); ++it){
        delete (*it);
    }
}

void Configuration::addConstant(const QString &str, Const::ConstObject* num){
    if(!this->constants.contains(str))
        this->constants[str] = num;
    this->mainWindow->addConstant(str, num);
}

double Configuration::getConstant(const QString &str) const{
    return *this->constants[str];
}

void Configuration::removeConstant(const QString &str){
    if(this->constants.contains(str))
        this->constants.remove(str);
    this->mainWindow->removeConstant(str);
}

const CMap<QString, Const::ConstObject*>& Configuration::getConstantList(){
    return this->constants;
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
