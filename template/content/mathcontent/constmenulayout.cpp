#include <QtWidgets/QScrollArea>
#include "constmenulayout.h"
#include "constmenuitem.h"
#include "../../mainwindow.h"
#include "calculator/calculator.h"
ConstMenuLayout::ConstMenuLayout(MainWindow* window, Template::Calculator* cal, QScrollArea *scrollArea) :
    MenuLayout(window, scrollArea), calculator(cal){
    QPushButton* constButton = cal->findChild<QPushButton*>("constButton");
    int width = constButton->width();
    this->setWidth(width-25);
}

void ConstMenuLayout::applyLayout(){
}

void ConstMenuLayout::show(){
    int index = 0;
    int length = calculator->getDoubleList()->count();
    int height = calculator->findChild<QPushButton*>("constButton")->height();
    int threshold = 7;
    ConstMenuItem *menuItem;
    this->moveTo(calculator->findChild<QPushButton*>("constButton"));
    if(length <= threshold){
        this->setHeight(height*length);
    }
    else{
        scrollArea->setFixedHeight(height*threshold);
        this->parent->setFixedHeight(height*length);
    }
    for(auto it = calculator->getDoubleList()->begin(); it != calculator->getDoubleList()->end(); ++it, ++index){
        QString str = it.key().chopped(1);
        str.remove(0, 1);
        menuItem = new ConstMenuItem(calculator, this->parent, str, index);
        menuItem->setToolTip(it.value().getDescription());
        connect(menuItem, &MenuItem::clicked, calculator, [this, it](){
            this->calculator->constant(it.key());
        });
        this->addItem(menuItem);
    }
    MenuLayout::show();
}
