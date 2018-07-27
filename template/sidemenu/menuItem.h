#ifndef MENUITEM_H
#define MENUITEM_H
#include <QPushButton>
#include <QString>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include "../mainwindow.h"
class MenuItem : public QPushButton{
    Q_OBJECT

private:
    QMainWindow *mainWindow;

public:
    MenuItem(QMainWindow *mainWindow, QWidget* parent, const QString &text, const int &num);
    MenuItem* selected();
    MenuItem* unselected();
};
#endif // MENUITEM_H
