#ifndef CONTENT_H
#define CONTENT_H
#include <QObject>
#include <QMap>
#include <QPushButton>
#define SETUP_UI(ui, widget) \
        ui->setupUi(widget); \
        foreach(QPushButton* button, widget->findChildren<QPushButton*>()){ \
            connect(button, &QPushButton::clicked, this, &this->buttonPushed); \
        }

namespace Template{
    class Content : public QObject{
        Q_OBJECT

    public:
        Content(QWidget*);
        virtual ~Content();
        virtual void setup() = 0;
        void addConstant(const QString &str, const double &num);
        void removeConstant(const QString &str);

    protected:
        QMap<QString, double> doubleList; // constant & repeating decimal symbolic calculation

    private:
        QWidget* contentWidget;

    public slots:
        virtual void buttonPushed() = 0;
    };
}

#endif // CONTENT_H
