#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <QObject>
#include <QString>
#include "../module/ctl.h"
namespace Template{
    class Configuration;
}
class MainWindow;

class Configuration : public QObject{
    Q_OBJECT

friend class Template::Configuration;

public:
    Configuration(MainWindow*);
    ~Configuration();
    void addConstant(const QString &str, const double &num);
    double getConstant(const QString &str) const;
    void removeConstant(const QString &str);
    const CMap<QString, double>* getConstantList();
    bool getRadian();
    int getPrecision();


private:
    CMap<QString, double> constants;
    MainWindow* mainWindow;
    bool radian;
    int precision;
    void setRadian(bool);
    void setPrecision(int);
};
#endif // CONFIGURATION_H
