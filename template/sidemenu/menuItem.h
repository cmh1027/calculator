#ifndef MENUITEM_H
#define MENUITEM_H
#include <QPushButton>
#include <QString>
#include <QtWidgets/QMainWindow>
#include <QSignalMapper>
#include "../mainwindow.h"
class MenuItem : public QPushButton{
    Q_OBJECT

public:
    MenuItem(QMainWindow *mainWindow, const QString &text, const int &num);
};
#endif // MENUITEM_H
