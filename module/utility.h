#ifndef UTILITY_H
#define UTILITY_H
#include <QString>
#include "ctl.h"
namespace Utility{
    QString doubleToString(const double &number);
    QString transformExpr(const QString& str, CMap<QString, double>& list);
}
#endif // UTILITY_H
