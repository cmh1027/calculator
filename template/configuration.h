#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <QObject>
#include <QMap>
#include <QString>
#include "../module/calculator/constant.h"
class Configuration : public QObject{
    Q_OBJECT

public:
    Configuration();
    void addConstant(const QString &str, const double &num);
    double getConstant(const QString &str) const;
    bool removeConstant(const QString &str);
    const QMap<QString, double>* getConstantList();

private:
    QMap<QString, double> constants;
};
#endif // CONFIGURATION_H
