#include "constmenuitem.h"
#include "calculator/calculator.h"
ConstMenuItem::ConstMenuItem(Template::Calculator* cal, QWidget* parent, const QString &text, const int &num) :
    MenuItem(parent, text){
    int height = cal->findChild<QPushButton*>("constButton")->height();
    int width = cal->findChild<QPushButton*>("constButton")->width();
    this->setFixedWidth(width);
    this->setFixedHeight(height);
    this->move(0, height*num);
    this->font(10, true);
    this->setStyleSheet("QPushButton{border:none; text-align: center;}"
                        "QPushButton:hover{background-color: rgb(207, 207, 207);}");
}
