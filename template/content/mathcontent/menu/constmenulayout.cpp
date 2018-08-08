#include <QtWidgets/QScrollArea>
#include "constmenulayout.h"
#include "constmenuitem.h"
#include "../../../../mainwindow.h"
#include "../../calculator/calculator.h"
ConstMenuLayout::ConstMenuLayout(MainWindow* window, Template::Calculator* cal, QScrollArea *scrollArea, QWidget* standard) :
    MenuLayout(window, scrollArea, standard), calculator(cal){
}


void ConstMenuLayout::click(){
    if(this->toggleOpen()){
        this->hide();
    }
    else{
        int index = 0;
        int length = calculator->getDoubleList()->count();
        ConstMenuItem *menuItem;
        this->moveToStandard();
        this->resizeToStandard(length);
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
}
