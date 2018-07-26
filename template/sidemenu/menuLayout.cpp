#include "menuLayout.h"
#include <iostream>
MenuLayout::MenuLayout(QMainWindow* window){
    this->setContentsMargins(0, 0, 0, 0);
    MenuItem *item;
    item = new MenuItem(window, "Normal", 0);
    item->setStyleSheet("background-color: rgb(119, 162, 255);");
    static_cast<MainWindow*>(window)->currentMenu = item;
    this->addWidget(item);
    this->addWidget(new MenuItem(window, "Scientific", 1));

}
