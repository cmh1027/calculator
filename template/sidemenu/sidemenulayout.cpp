#include <QtWidgets/QWidget>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QToolButton>
#include "sidemenulayout.h"
#include "../mainwindow.h"
#include "sidemenuitem.h"

SideMenuLayout::SideMenuLayout(MainWindow* window, QScrollArea* scrollArea) : MenuLayout(window, scrollArea),
    mainWindow(window){
    int width = scrollArea->findChild<QWidget*>("menuTitleWidget")->width();
    this->setWidth(width);
    this->setHeight(this->mainWindow->height());
    connect(scrollArea->findChild<QToolButton*>("menuCloseButton"), &QToolButton::clicked, window, &window->hideSideMenu);
}

void SideMenuLayout::applyLayout(){
    this->addItem((new SideMenuItem(mainWindow, this->parent, "Normal", 0))->selected());
    this->addItem((new SideMenuItem(mainWindow, this->parent, "Scientific", 1)));
    this->addItem((new SideMenuItem(mainWindow, this->parent, "Table", 2)));
    this->addItem((new SideMenuItem(mainWindow, this->parent, "Graph", 3)));
    this->addItem((new SideMenuItem(mainWindow, this->parent, "Matrix", 4)));
    this->addItem((new SideMenuItem(mainWindow, this->parent, "Configuration", 5)));
}
