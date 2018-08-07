#ifndef SIDEMENULAYOUT_H
#define SIDEMENULAYOUT_H
#include "../menulayout.h"

class MainWindow;
class MenuItem;
class QScrollArea;

class SideMenuLayout : public MenuLayout{
    Q_OBJECT

private:
    MainWindow *mainWindow;

public:
    SideMenuLayout(MainWindow*, QScrollArea*);
    virtual ~SideMenuLayout() = default;
    void applyLayout() override;

};
#endif // SIDEMENULAYOUT_H
