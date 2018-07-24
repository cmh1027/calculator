#ifndef CONTENT_H
#define CONTENT_H
#include <QMainWindow>
#define SETUP_UI this->contentUi->setupUi(this->MainWindow->findChild<QWidget*>("contentWidget"))

class Content : public QObject{
    Q_OBJECT

public:
    Content();
    virtual ~Content();

public slots:
    virtual void buttonPushed() = 0;

};


#endif // CONTENT_H
