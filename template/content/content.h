#ifndef CONTENT_H
#define CONTENT_H
#include <QObject>
#include <QMainWindow>
#include <QLayout>
#include "../../module/utility.h"

class Content : public QObject{
    Q_OBJECT

public:
    Content(QWidget *window);
    virtual ~Content();
    virtual void setup() = 0;
    void hideAllObjects();
    void showAllObjects();
    void deleteAllObjects();

private:
    QWidget* contentWidget;

public slots:
    virtual void buttonPushed() = 0;
};


#endif // CONTENT_H
