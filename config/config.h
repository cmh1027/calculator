#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <QObject>
#include <QMap>
#include <QString>

class MainWindow;

class Configuration : public QObject{
    Q_OBJECT

public:
    Configuration(MainWindow*);
    ~Configuration();
    void addConstant(const QString &str, const double &num);
    double getConstant(const QString &str) const;
    void removeConstant(const QString &str);
    const QMap<QString, double>* getConstantList();
    bool getRadian();
    void setRadian(bool);
    int getPrecision();
    void setPrecision(int);

private:
    QMap<QString, double> constants;
    MainWindow* mainWindow;
    bool radian;
    int precision;
};
#endif // CONFIGURATION_H
