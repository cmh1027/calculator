#ifndef CONSTMENU_H
#define CONSTMENU_H
#include "../../../../menulayout.h"
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
    ConstMenuLayout(MainWindow*, Template::Calculator*, QScrollArea*, QWidget*);
    virtual ~ConstMenuLayout() = default;
    void click();
};

#endif // CONSTMENU_H
