#ifndef SIDEMENUITEM_H
#define SIDEMENUITEM_H
#include "../menuitem.h"

class MainWindow;
class QString;
class QWidget;

class SideMenuItem : public MenuItem{
    Q_OBJECT

private:
    MainWindow *mainWindow;

public:
    SideMenuItem(MainWindow *mainWindow, QWidget* parent, const QString &text, const int &num);
    virtual ~SideMenuItem() = default;
    SideMenuItem* selected();
    SideMenuItem* unselected();
};
#endif // SIDEMENUITEM_H
