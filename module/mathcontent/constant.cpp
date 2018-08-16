#include <QString>
#include "constant.h"
#include "calculation.h"
#include "../exception.h"
#define _USE_MATH_DEFINES
#include <cmath>

namespace Const{
    ConstObject::ConstObject(const double& val, const bool& defaultFlag, const bool& tempFlag, const QString& str) :
        DataObject(str, defaultFlag, tempFlag), value(val) {
    }

    ConstObject::operator double() const{
        return this->value;
    }

    double ConstObject::getValue() const{
        return this->value;
    }

    void ConstObject::setValue(const double& value){
        this->value = value;
        this->expression.clear();
    }

    QString ConstObject::getExpr() const{
        return this->expression;
    }

    void ConstObject::setExpr(const QString& expr){
        this->expression = expr;
    }

    void ConstObject::setExpr(const QString& expr, CMap<QString, Const::ConstObject*>& doubleList){
        bool isDouble;
        QString &&value = Calculation::calculateExpr(expr, doubleList);
        value.toDouble(&isDouble);
        if(isDouble){
            this->value = value.toDouble();
        }
        else if(value.indexOf("{") != -1 && value.indexOf("}") != -1){
            this->value = *doubleList.value(value);
            doubleList.remove(value);
        }
        else{
            this->value = std::nan("");
        }
        this->expression = expr;
    }

    bool ConstObject::update(CMap<QString, Const::ConstObject*>& doubleList){
        bool isUpdated = false;
        bool isDouble;
        if(!this->expression.isEmpty()){
            QString value = Calculation::calculateExpr(this->expression, doubleList);
            value.toDouble(&isDouble);
            if(isDouble){
                this->value = value.toDouble();
            }
            else if(value.indexOf("{") != -1 && value.indexOf("}") != -1){
                double result = *doubleList.value(value);
                if(this->value != *doubleList.value(value)){
                    doubleList.remove(value);
                    isUpdated = true;
                }
                this->value = result;
            }
            else{
                this->value = std::nan("");
            }
        }
        return isUpdated;
    }
    const double PI = M_PI;
    const double E = M_E;
}
