#ifndef MENULAYOUT_H
#define MENULAYOUT_H
#include <QtWidgets/QWidget>

class MainWindow;

class MenuLayout : public QObject{
    Q_OBJECT

public:
    MenuLayout(MainWindow*, QWidget*);
    void applyLayout();
    void addWidget(QWidget*);

private:
    MainWindow *mainWindow;
    QWidget *parent;
};
#endif // MENULAYOUT_H
