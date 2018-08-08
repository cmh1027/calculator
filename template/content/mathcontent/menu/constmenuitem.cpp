#include "constmenuitem.h"
#include "../../calculator/calculator.h"
ConstMenuItem::ConstMenuItem(Template::Calculator* cal, QWidget* parent, const QString &text, const int &num) :
    MenuItem(parent, text, cal->findChild<QPushButton*>("constButton"), num){
    this->font(10, true);
    this->setStyleSheet("QPushButton{border:none; text-align: center;}"
                        "QPushButton:hover{background-color: rgb(207, 207, 207);}");
}
