#ifndef FUNCMENU_H
#define FUNCMENU_H
#include "../../../../menulayout.h"
class MainWindow;
class QString;
namespace Template{
    class Calculator;
}

class FuncMenuLayout : public MenuLayout{
    Q_OBJECT

private:
    Template::Calculator *calculator;

public:
    FuncMenuLayout(MainWindow*, Template::Calculator*, QScrollArea*, QWidget*);
    virtual ~FuncMenuLayout() = default;
    void click();
};

#endif // CONSTMENU_H
