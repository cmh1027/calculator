#ifndef UTILITY_H
#define UTILITY_H
#include "calculator/constant.h"
#include "ctl.h"
class QString;
namespace Utility{
    QString doubleToString(const double &number);
    QString transformExpr(const QString& str, CMap<QString, Const::ConstObject>& list);
}
#endif // UTILITY_H
