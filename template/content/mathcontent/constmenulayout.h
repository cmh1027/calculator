#ifndef CONSTMENU_H
#define CONSTMENU_H
#include "../../menulayout.h"
#include <functional>
class MainWindow;
class QString;
namespace Template{
    class Calculator;
}

class ConstMenuLayout : public MenuLayout{
    Q_OBJECT

private:
    Template::Calculator *calculator;

public:
    ConstMenuLayout(MainWindow*, Template::Calculator*, QScrollArea*);
    virtual ~ConstMenuLayout() = default;
    void applyLayout() override;
    void show();
};

#endif // CONSTMENU_H
