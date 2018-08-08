#include <QString>
#include "constant.h"
#define _USE_MATH_DEFINES
#include <cmath>
namespace Const{
    ConstObject::ConstObject(const double& val, const QString& str, const bool& flag) :
        DataObject(str, flag), value(val) {
    }

    ConstObject::operator double() const{
        return this->value;
    }

    const double PI = M_PI;
    const double E = M_E;
}
