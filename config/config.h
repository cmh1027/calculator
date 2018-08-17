#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <QObject>
#include "../module/ctl.h"
#include "../module/mathcontent/constant.h"
#include "../module/mathcontent/operator.h"

namespace Template{
    class Configuration;
}
class QString;
class MainWindow;

namespace Configuration{
    class Configuration{

    friend class Template::Configuration;

    public:
        Configuration(MainWindow*);
        virtual ~Configuration();
        void addConstant(const QString &str, Const::ConstObject* num);
        double getConstant(const QString &str) const;
        void removeConstant(const QString &str);
        void addFunction(const QString &str, Operation::OperationObject& num);
        void removeFunction(const QString &str);
        CMap<QString, Const::ConstObject*>& getConstantList();
        CMap<QString, Operation::OperationObject>& getFuncList();
        bool getRadian();
        int getPrecision();
        void refreshAllContents();


    private:
        CMap<QString, Const::ConstObject*> constants;
        CMap<QString, Operation::OperationObject> operateFuncs;
        QVector<Const::ConstObject*> deleted;
        MainWindow* mainWindow;
        bool radian;
        int precision;
        void setRadian(const bool&);
        void setPrecision(const int&);
    };
}
#endif // CONFIGURATION_H
