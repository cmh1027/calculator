#include <QString>
#include <QtWidgets/QWidget>
#include "menuitem.h"

MenuItem::MenuItem(QWidget *parent, const QString &text, QWidget* std, const int &num) : QPushButton(), standard(std){
    this->setFixedWidth(parent->width());
    this->setText(text);
    if(std != nullptr){
        this->setFixedWidth(std->width());
        this->setFixedHeight(std->height());
        this->move(0, std->height()*num);
        Q_ASSERT(num != -1);
    }
}

void MenuItem::font(int size, bool bold){
    QFont font;
    font.setFamily(QString::fromUtf8("\353\247\221\354\235\200 \352\263\240\353\224\225"));
    font.setPointSize(size);
    font.setBold(bold);
    this->setFont(font);
}
