#ifndef UTILITY_H
#define UTILITY_H
#include <QString>
#include <QMap>
namespace Utility{
    QString doubleToString(const double &number);
    QString transformExpr(const QString& str, QMap<QString, double>& list);
}
#endif // UTILITY_H
