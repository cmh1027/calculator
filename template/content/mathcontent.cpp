#include "mathcontent.h"
#include "../../config/config.h"

extern Configuration* config;

namespace Template{
    MathContent::MathContent(MainWindow* window) : Content(window),
        doubleList(*config->getConstantList()), contentWidget(this){}

    MathContent::~MathContent(){}

    void MathContent::addConstant(const QString &str, const Const::ConstObject& num){
        this->doubleList[str] = num;
    }

    void MathContent::removeConstant(const QString &str){
        if(this->doubleList.contains(str))
            this->doubleList.remove(str);
    }
}
