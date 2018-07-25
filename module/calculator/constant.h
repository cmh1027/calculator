#ifndef CONSTANT_H
#define CONSTANT_H
#define _USE_MATH_DEFINES
#include <cmath>
#include <QMap>
#include <QString>
#include <sstream>
#include <iomanip>


namespace Const{
    extern QMap<QString, double> Constant;
}
QString doubleToString(const double &number, int precision = 6);
// void round(double& number, const int &precision);
#endif // CONSTANT_H
