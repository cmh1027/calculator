#ifndef CONTENT_H
#define CONTENT_H
#include <QObject>
#define SETUP_CAL_UI(ui, window) ui->setupUi(window->findChild<QWidget*>("contentWidget")); \
        Calculator::bindLabels();

class Content : public QObject{
    Q_OBJECT

public:
    Content();
    virtual ~Content();
    virtual void setup() = 0;


public slots:
    virtual void buttonPushed() = 0;

};


#endif // CONTENT_H
