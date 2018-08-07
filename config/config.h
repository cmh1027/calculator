#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <QObject>
#include "../module/ctl.h"
#include "../module/calculator/constant.h"

namespace Template{
    class Configuration;
}
class QString;
class MainWindow;

class Configuration : public QObject{
    Q_OBJECT

friend class Template::Configuration;

public:
    Configuration(MainWindow*);
    virtual ~Configuration() = default;
    void addConstant(const QString &str, const Const::ConstObject& num);
    double getConstant(const QString &str) const;
    void removeConstant(const QString &str);
    const CMap<QString, Const::ConstObject>* getConstantList();
    bool getRadian();
    int getPrecision();


private:
    CMap<QString, Const::ConstObject> constants;
    MainWindow* mainWindow;
    bool radian;
    int precision;
    void setRadian(bool);
    void setPrecision(int);
};
#endif // CONFIGURATION_H
