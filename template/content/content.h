#ifndef CONTENT_H
#define CONTENT_H
#include <QObject>
#include <QMainWindow>
#include <QLayout>
#include "../../module/utility.h"

class Content : public QObject{
    Q_OBJECT

public:
    Content(QMainWindow*, QWidget *window);
    virtual ~Content();
    virtual void setup() = 0;
    void hideAllObjects();
    void showAllObjects();
    void deleteAllObjects();

private:
    QWidget* contentWidget;
    QMainWindow* mainWindow;

public slots:
    virtual void buttonPushed() = 0;
};


#endif // CONTENT_H
