#include "constmenuitem.h"
#include "../../calculator/calculator.h"
ConstMenuItem::ConstMenuItem(Template::Calculator* cal, QWidget* parent, const QString &text, const int &num) :
    MathMenuItem(parent, text.chopped(1).remove(0, 1), cal->findChild<QPushButton*>("constButton"), num){
}
