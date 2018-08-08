#include <QtWidgets/QScrollArea>
#include "funcmenulayout.h"
#include "funcmenuitem.h"
#include "../../../../mainwindow.h"
#include "../../calculator/calculator.h"
#include "../../../../../module/calculator/operator.h"
FuncMenuLayout::FuncMenuLayout(MainWindow* window, Template::Calculator* cal, QScrollArea *scrollArea, QWidget* standard) :
    MenuLayout(window, scrollArea, standard), calculator(cal){
}


void FuncMenuLayout::click(){
    if(this->toggleOpen()){
        this->hide();
    }
    else{
        int index = 0;
        int length = Operator::operateFuncs.count();
        FuncMenuItem *menuItem;
        this->moveToStandard();
        this->resizeToStandard(length);
        for(auto it = Operator::operateFuncs.begin(); it != Operator::operateFuncs.end(); ++it, ++index){
            menuItem = new FuncMenuItem(calculator, this->parent, it.key(), index);
            menuItem->setToolTip(it.value().getDescription());
            connect(menuItem, &MenuItem::clicked, calculator, [this, it](){

            });
            this->addItem(menuItem);
        }
        MenuLayout::show();
    }
}
