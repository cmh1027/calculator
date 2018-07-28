#ifndef MENUITEM_H
#define MENUITEM_H
#include <QPushButton>
#include <QString>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

class MainWindow;

class MenuItem : public QPushButton{
    Q_OBJECT

private:
    MainWindow *mainWindow;

public:
    MenuItem(MainWindow *mainWindow, QWidget* parent, const QString &text, const int &num);
    MenuItem* selected();
    MenuItem* unselected();
};
#endif // MENUITEM_H
