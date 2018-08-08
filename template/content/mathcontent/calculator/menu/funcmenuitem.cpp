#include "funcmenuitem.h"
#include "../../calculator/calculator.h"
FuncMenuItem::FuncMenuItem(Template::Calculator* cal, QWidget* parent, const QString &text, const int &num) :
    MathMenuItem(parent, text, cal->findChild<QPushButton*>("functionButton"), num){
}
