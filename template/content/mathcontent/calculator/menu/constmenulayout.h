#ifndef CONSTMENU_H
#define CONSTMENU_H
#include "../../mathmenulayout.h"
class MainWindow;
class QString;
namespace Template{
    class Calculator;
}

class ConstMenuLayout : public MathMenuLayout{
    Q_OBJECT

private:
    Template::Calculator *calculator;

public:
    ConstMenuLayout(MainWindow*, Template::Calculator*, QScrollArea*, QWidget*);
    virtual ~ConstMenuLayout() = default;
    void click();
};

#endif // CONSTMENU_H
