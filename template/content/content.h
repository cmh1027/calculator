#ifndef CONTENT_H
#define CONTENT_H
#include <QWidget>
#define SETUP_UI(ui, widget) \
        ui->setupUi(widget); \
        this->buttonConnect(); \

#define SETUP_UI_CAL(ui, widget) \
        SETUP_UI(ui, widget) \
        this->installMenu(); \

class MainWindow;

namespace Template{
    class Content : public QWidget{
        Q_OBJECT

    public:
        Content(MainWindow*);
        virtual ~Content() = default;
        virtual void setup() = 0;

    protected:
        virtual void buttonConnect() = 0; // must be in setup() function
        MainWindow* mainWindow;

    private:
        QWidget* contentWidget;

    };
}

#endif // CONTENT_H
