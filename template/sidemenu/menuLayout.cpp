#include "menuLayout.h"

MenuLayout::MenuLayout(QMainWindow* window){
    this->setContentsMargins(0, 0, 0, 0);
    MenuItem *item;
    item = new MenuItem(window, "Normal", 0);
    item->setStyleSheet("background-color:red;");
    this->addWidget(item);
    item = new MenuItem(window, "Scientific", 1);
    item->setStyleSheet("background-color:blue;");
    this->addWidget(item);
}
