#include <QtWidgets/QWidget>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStackedWidget>
#include <QStyle>
#include "menulayout.h"
#include "mainwindow.h"
#include "menuitem.h"
MenuLayout::MenuLayout(MainWindow* window, QScrollArea* scrollArea, QWidget* std) : scrollArea(scrollArea),
    isOpen(false), maxMenuCount(7), mainWindow(window),
    parent(scrollArea->findChild<QWidget*>()->findChild<QWidget*>()), standard(std){
    scrollArea->setParent(window);
    scrollArea->hide();
    if(std != nullptr){
        this->setWidth(std->width()-25);
    }
}

MenuLayout::~MenuLayout(){
    foreach(MenuItem* item, this->items){
        delete item;
    }
}

void MenuLayout::addItem(MenuItem* item){
    item->setParent(this->parent);
    this->items.push_back(item);
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

void MenuLayout::moveToStandard(){
    int x = 0, y = 0;
    if(this->standard == nullptr){
        Q_ASSERT(this->standard != nullptr);
        return;
    }
    QWidget *widget = this->standard;
    x += this->mainWindow->contentWidget->x();
    y += this->mainWindow->contentWidget->y();
    while(widget != nullptr && widget != mainWindow->contentWidget){
        x += widget->x();
        y += widget->y();
        widget = dynamic_cast<QWidget*>(widget->parent());
        Q_ASSERT(widget != nullptr);
    }
    scrollArea->move(x, y + this->standard->height());
}

bool MenuLayout::toggleOpen(){
    bool temp = this->isOpen;
    this->isOpen = !this->isOpen;
    return temp;
}

void MenuLayout::resizeToStandard(int length){
    if(this->standard == nullptr){
        Q_ASSERT(this->standard != nullptr);
        return;
    }
    int height = this->standard->height();
    if(length <= this->maxMenuCount){
        this->setHeight(height*length);
        this->parent->setStyleSheet("");
    }
    else{
        scrollArea->setFixedHeight(height*this->maxMenuCount);
        this->parent->setFixedHeight(height*length);
        this->parent->setStyleSheet(QString("QWidget{padding-right:%1px}").arg(QStyle::PM_ScrollBarExtent));
    }
}
