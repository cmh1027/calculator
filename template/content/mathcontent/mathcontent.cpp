#include <QtWidgets/QWidget>
#include <QtWidgets/QScrollArea>
#include <QString>
#include "mathcontent.h"
#include "mathmenulayout.h"
#include "../../../config/config.h"
extern Configuration* config;

namespace Template{
    MathContent::MathContent(MainWindow* window) : Content(window),
        doubleList(*config->getConstantList()), contentWidget(this){}

    MathContent::~MathContent(){
        foreach(MathMenuLayout* layout, this->menus){
            delete layout;
        }
    }

    void MathContent::addConstant(const QString &str, const Const::ConstObject& num){
        if(!this->doubleList.contains(str))
            this->doubleList[str] = num;
    }

    void MathContent::removeConstant(const QString &str){
        if(this->doubleList.contains(str))
            this->doubleList.remove(str);
    }

    const CMap<QString, Const::ConstObject>& MathContent::getDoubleList(){
        return this->doubleList;
    }

    void MathContent::mousePressEvent(QMouseEvent*){
        foreach(MathMenuLayout *menu, this->menus){
            if(menu->scrollArea->underMouse())
                return;
        }
        this->hideAllMenus();
    }

    void MathContent::hideAllMenus(){
        foreach(MathMenuLayout *menu, this->menus){
            menu->hide();
        }
    }

    void MathContent::moveAllMenus(){
        foreach(MathMenuLayout *menu, this->menus){
            menu->moveToStandard();
        }
    }
}
