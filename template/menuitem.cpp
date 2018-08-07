#include <QString>
#include <QtWidgets/QWidget>
#include "menuitem.h"

MenuItem::MenuItem(QWidget *parent, const QString &text) : QPushButton(){
    this->setFixedWidth(parent->width());
    this->setText(text);
}

void MenuItem::font(int size, bool bold){
    QFont font;
    font.setFamily(QString::fromUtf8("\353\247\221\354\235\200 \352\263\240\353\224\225"));
    font.setPointSize(size);
    font.setBold(bold);
    this->setFont(font);
}
