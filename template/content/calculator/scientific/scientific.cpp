#include "scientific.h"
#include "ui_scientific.h"
ScientificCalculator::ScientificCalculator(QMainWindow* window) : GeneralCalculator(window), contentUi(new Ui::Form),
    MainWindow(window)
{}

ScientificCalculator::~ScientificCalculator(){}

void ScientificCalculator::setup(){
    SETUP_CAL_UI(contentUi, MainWindow)
    auto allButtons = MainWindow->findChildren<QPushButton*>();
    foreach(QPushButton* button, allButtons){
        connect(button, SIGNAL(clicked()), this, SLOT(buttonPushed()));
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

void ScientificCalculator::mod(){
    this->unarySpecial(Operator::Special::mod);
}

void ScientificCalculator::fac(){
    this->unarySpecial(Operator::Special::fac);
}
