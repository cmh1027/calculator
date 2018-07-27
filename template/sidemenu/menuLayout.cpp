#include "menuLayout.h"
#include <iostream>
MenuLayout::MenuLayout(QMainWindow* window, QWidget* widget):mainWindow(window), parent(widget){}

void MenuLayout::applyLayout(){
    this->addWidget((new MenuItem(mainWindow, parent, "Normal", 0))->selected());
    this->addWidget((new MenuItem(mainWindow, parent, "Scientific", 1))->unselected());
}

void MenuLayout::addWidget(QWidget* item){
    item->setParent(this->parent);
}
