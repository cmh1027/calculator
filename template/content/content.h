#ifndef CONTENT_H
#define CONTENT_H
#include <QObject>

class MainWindow;

class Content : public QObject{
    Q_OBJECT

public:
    Content(MainWindow*, QWidget *window);
    virtual ~Content();
    virtual void setup() = 0;

private:
    QWidget* contentWidget;
    MainWindow* mainWindow;

public slots:
    virtual void buttonPushed() = 0;
};


#endif // CONTENT_H
