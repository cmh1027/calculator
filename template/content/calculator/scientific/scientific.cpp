#include "scientific.h"
#include "ui_scientific.h"
#include <iostream>
ScientificCalculator::ScientificCalculator(QMainWindow* window) : GeneralCalculator(window),
    contentUi(new Ui::ScientificCalculator), MainWindow(window)
{
    for(auto iter = GeneralCalculator::Operators.constBegin(); iter != GeneralCalculator::Operators.constEnd(); ++iter){
        Operators[iter.key()] = iter.value();
    }
    Operators["root"] = this->root;
    Operators["pow"] = this->pow;
    Operators["sin"] = this->sin;
    Operators["cos"] = this->cos;
    Operators["tan"] = this->tan;
    Operators["asin"] = this->asin;
    Operators["acos"] = this->acos;
    Operators["atan"] = this->atan;
    Operators["sinh"] = this->sinh;
    Operators["cosh"] = this->cosh;
    Operators["tanh"] = this->tanh;
    Operators["log"] = this->log;
    Operators["ln"] = this->ln;
    Operators["mod"] = this->mod;
    Operators["fac"] = this->fac;
    Operators["abs"] = this->abs;
    Operators["pi"] = this->pi;
    Operators["e"] = this->e;
}
ScientificCalculator::~ScientificCalculator(){}

void ScientificCalculator::setup(){
    SETUP_CAL_UI(contentUi, MainWindow)
}

void ScientificCalculator::buttonPushed(){
    QRegExp rx("num[0-9]{1}Button");
    auto button = sender();
    QString buttonName = button->objectName();
    if(rx.exactMatch(buttonName)){
        this->addNumber(buttonName.mid(3, 1));
    }
    else{
        QString funcName = buttonName.chopped(6);
        if(this->Operators.contains(funcName))
            (this->*(this->Operators[funcName]))();
        else{
            std::cout << "Map Operators does not have a key : " << funcName.toStdString() << "\n";
            std::cout << "in " << __FILE__ << " : " << __LINE__ << "\n";
            exit(1);
        }
    }
}

void ScientificCalculator::binarySpecial(const QString &op){
    if(this->getInter().isEmpty() || !this->calculated){
        this->appendInter(this->getResult());
        this->appendInter(op);
    }
    else{
        if(this->isLastOpArithmetic())
            this->replaceLastOp(op);
        else
            this->appendInter(op);
    }
    this->specialStart = true;
    this->calculated = false;
}

void ScientificCalculator::root(){
    this->binarySpecial(Operator::Special::root);
}

void ScientificCalculator::pow(){
    this->binarySpecial(Operator::Special::pow);
}

void ScientificCalculator::sin(){
    this->unarySpecial(Operator::Special::sin);
}

void ScientificCalculator::cos(){
    this->unarySpecial(Operator::Special::pow);
}

void ScientificCalculator::tan(){
    this->unarySpecial(Operator::Special::tan);
}

void ScientificCalculator::asin(){
    this->unarySpecial(Operator::Special::asin);
}

void ScientificCalculator::acos(){
    this->unarySpecial(Operator::Special::acos);
}

void ScientificCalculator::atan(){
    this->unarySpecial(Operator::Special::atan);
}

void ScientificCalculator::sinh(){
    this->unarySpecial(Operator::Special::sinh);
}

void ScientificCalculator::cosh(){
    this->unarySpecial(Operator::Special::cosh);
}

void ScientificCalculator::tanh(){
    this->unarySpecial(Operator::Special::tanh);
}

void ScientificCalculator::log(){
    this->unarySpecial(Operator::Special::log);
}

void ScientificCalculator::ln(){
    this->unarySpecial(Operator::Special::ln);
}

void ScientificCalculator::mod(){
    this->unarySpecial(Operator::Special::mod);
}

void ScientificCalculator::fac(){
    this->unarySpecial(Operator::Special::fac);
}

void ScientificCalculator::abs(){
    this->unarySpecial(Operator::Special::abs);
}

void ScientificCalculator::pi(){
    this->constant(Constant["pi"]);
}

void ScientificCalculator::e(){
    this->constant(Constant["e"]);
}
