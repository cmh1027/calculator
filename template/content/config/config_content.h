#ifndef CONFIG_H
#define CONFIG_H
#include <QWidget>
#include <QString>
#include <QMap>

namespace Ui {
    class Configuration;
}
class MainWindow;

namespace Template{
    class Configuration : public QObject{
        Q_OBJECT

    public:
        Configuration(MainWindow*, QWidget*);
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
