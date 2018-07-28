#include "configuration.h"
#include "../module/calculator/constant.h"

Configuration::Configuration():constants({{"{pi}", Const::Constant["pi"]}, {"{e}", Const::Constant["e"]}}){}

void Configuration::addConstant(const QString &str, const double &num){
    this->constants[str] = num;
}

double Configuration::getConstant(const QString &str) const{
    return this->constants[str];
}

bool Configuration::removeConstant(const QString &str){
    if(this->constants.contains(str)){
        this->constants.remove(str);
        return true;
    }
    else{
        return false;
    }
}

const QMap<QString, double>* Configuration::getConstantList(){
    return &constants;
}
