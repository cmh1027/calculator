#include <QtWidgets/QWidget>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStackedWidget>
#include "menulayout.h"
#include "mainwindow.h"
#include "menuitem.h"
MenuLayout::MenuLayout(MainWindow* window, QScrollArea* scrollArea) : scrollArea(scrollArea), mainWindow(window),
    parent(scrollArea->findChild<QWidget*>("scrollAreaWidgetContents")){
    scrollArea->setParent(window);
    scrollArea->hide();
}


void MenuLayout::addItem(MenuItem* item){
    item->setParent(this->parent);
    items.push_back(item);
}

void MenuLayout::setHeight(int height){
    scrollArea->setFixedHeight(height);
    this->parent->setFixedHeight(height);
}

void MenuLayout::setWidth(int width){
    scrollArea->setFixedWidth(width);
    this->parent->setFixedWidth(width);
}

void MenuLayout::show(){
    scrollArea->show();
}

void MenuLayout::hide(){
    scrollArea->hide();
}

void MenuLayout::moveTo(QWidget* standard){
    int x = 0, y = 0;
    QWidget *widget = standard;
    x += this->mainWindow->contentWidget->x();
    y += this->mainWindow->contentWidget->y();
    while(widget != nullptr && widget != mainWindow->contentWidget){
        x += widget->x();
        y += widget->y();
        widget = dynamic_cast<QWidget*>(widget->parent());
        Q_ASSERT(widget != nullptr);
    }
    scrollArea->move(x, y + standard->height());
}
