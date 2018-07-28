#include "content.h"
#include <iostream>
#include "../mainwindow.h"
#include "../../config/config.h"

extern Configuration* config;

namespace Template{
    Content::Content(QWidget* widget) : doubleList(*config->getConstantList()),
        contentWidget(widget)
    {

    }

    Content::~Content(){}

    void Content::addConstant(const QString &str, const double &num){
        this->doubleList[str] = num;
    }

    void Content::removeConstant(const QString &str){
        if(this->doubleList.contains(str))
            this->doubleList.remove(str);
    }
}
