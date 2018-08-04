#ifndef CONFIG_H
#define CONFIG_H
#include <QWidget>
#include <QString>
#include "../../../module/ctl.h"

namespace Ui {
    class Configuration;
}
class MainWindow;

namespace Template{
    class Configuration : public QWidget{
        Q_OBJECT

    public:
        Configuration(MainWindow*);
        virtual ~Configuration();
        void setup();

    private:
        Ui::Configuration *contentUi;
        MainWindow *mainWindow;
        QWidget *contentWidget;
        void buttonConnect();
    };
}
#endif // CONFIG_H
