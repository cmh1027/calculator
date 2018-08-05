#ifndef CONTENT_H
#define CONTENT_H
#include <QWidget>
#define SETUP_UI(ui, widget) \
        ui->setupUi(widget); \
        this->buttonConnect();

class MainWindow;

namespace Template{
    class Content : public QWidget{
        Q_OBJECT

    public:
        Content(MainWindow*);
        virtual ~Content();
        virtual void setup() = 0;

    protected:
        virtual void buttonConnect() = 0;
        MainWindow* mainWindow;

    private:
        QWidget* contentWidget;
    };
}

#endif // CONTENT_H
