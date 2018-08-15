#include <QtWidgets/QScrollArea>
#include "constmenulayout.h"
#include "constmenuitem.h"
#include "../../../../mainwindow.h"
#include "../../calculator/calculator.h"
ConstMenuLayout::ConstMenuLayout(MainWindow* window, Template::Calculator* cal, QScrollArea *scrollArea, QWidget* standard) :
    MathMenuLayout(window, scrollArea, standard), calculator(cal){
}


void ConstMenuLayout::click(){
    if(this->toggleOpen()){
        this->hide();
    }
    else{
        int index = 0;
        ConstMenuItem *menuItem;
        for(auto it = calculator->getDoubleList().begin(); it != calculator->getDoubleList().end(); ++it, ++index){
            menuItem = new ConstMenuItem(calculator, this->parent, it.key(), index);
            menuItem->setToolTip(it.value()->getDescription());
            connect(menuItem, &MenuItem::clicked, calculator, [this, it](){
                this->calculator->constant(it.key());
            });
            this->addItem(menuItem);
        }
        this->moveToStandard();
        this->resizeToStandard(index);
        this->show();
    }
}
