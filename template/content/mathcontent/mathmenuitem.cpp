#include "mathmenuitem.h"
MathMenuItem::MathMenuItem(QWidget* parent, const QString &text, QWidget* standard, const int &num) :
    MenuItem(parent, text, standard, num){
    this->font(10, true);
    this->setStyleSheet("QPushButton{border:none; text-align: center;}"
                        "QPushButton:hover{background-color: rgb(207, 207, 207);}");
}
