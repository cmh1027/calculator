#ifndef MENULAYOUT_H
#define MENULAYOUT_H
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include "menuitem.h"

class MenuLayout : public QObject{
    Q_OBJECT

public:
    MenuLayout(QMainWindow*, QWidget*);
    void applyLayout();
    void addWidget(QWidget*);

private:
    QMainWindow *mainWindow;
    QWidget *parent;
};
#endif // MENULAYOUT_H
