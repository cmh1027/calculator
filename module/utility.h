#ifndef UTILITY_H
#define UTILITY_H
#include <QString>
#include "calculator/constant.h"
#include "ctl.h"
namespace Utility{
    QString doubleToString(const double &number);
    QString transformExpr(const QString& str, CMap<QString, Const::ConstObject>& list);
}
#endif // UTILITY_H
