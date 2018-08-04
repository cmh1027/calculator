#include "content.h"
#include "../mainwindow.h"
#include "../../config/config.h"

extern Configuration* config;

namespace Template{
    Content::Content() : QWidget(), doubleList(*config->getConstantList()), contentWidget(this){}

    Content::~Content(){}

    void Content::addConstant(const QString &str, const double &num){
        this->doubleList[str] = num;
    }

    void Content::removeConstant(const QString &str){
        if(this->doubleList.contains(str))
            this->doubleList.remove(str);
    }
}
