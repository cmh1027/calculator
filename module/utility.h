#ifndef UTILITY_H
#define UTILITY_H
#include <QString>
#include <sstream>
#include <iomanip>
#include <QMap>
#include <iostream>
namespace Utility{
    QString doubleToString(const double &number, int precision = -1);
    QString transformExpr(QString str, QMap<QString, double>& list);
}
#endif // UTILITY_H
