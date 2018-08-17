#include <QtWidgets/QScrollArea>
#include "funcmenulayout.h"
#include "funcmenuitem.h"
#include "../../../../mainwindow.h"
#include "../../calculator/calculator.h"
#include "../../calculator/general/general.h"
#include "../../calculator/scientific/scientific.h"
#include "../../../../../config/config.h"
#include "../../../../../module/mathcontent/operator.h"
extern Configuration::Configuration* config;

FuncMenuLayout::FuncMenuLayout(MainWindow* window, Template::Calculator* cal, QScrollArea *scrollArea, QWidget* standard) :
    MathMenuLayout(window, scrollArea, standard), calculator(cal){
}


void FuncMenuLayout::click(){
    if(this->toggleOpen()){
        this->hide();
    }
    else{
        int index = 0;
        FuncMenuItem *menuItem;
        for(auto it = config->getFuncList().begin(); it != config->getFuncList().end(); ++it, ++index){
            if(it.value().getArity() == Operation::Arithmetic){
                --index;
                continue;
            }
            menuItem = new FuncMenuItem(calculator, this->parent, it.key(), index);
            menuItem->setToolTip(it.value().getDescription());
            connect(menuItem, &MenuItem::clicked, calculator, [this, it](){
                switch(it.value().getArity()){
                    case Operation::Arithmetic:
                        break;
                    case Operation::Unary:
                        static_cast<Template::GeneralCalculator*>(this->calculator)->unarySpecial(it.key());
                        break;
                    case Operation::Binary:
                        static_cast<Template::ScientificCalculator*>(this->calculator)->binarySpecial(it.key());
                        break;
                }
            });
            this->addItem(menuItem);
        }
        this->moveToStandard();
        this->resizeToStandard(index);
        this->show();
    }
}
