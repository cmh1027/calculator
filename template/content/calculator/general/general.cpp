#include "general.h"
#include "ui_general.h"
GeneralCalculator::GeneralCalculator(QMainWindow *window) :
    Calculator(window), contentUi(new Ui::Form), MainWindow(window),
    Operators(std::initializer_list<std::pair<QString, void(GeneralCalculator::*)()>>({
        std::make_pair("plus", this->plus), std::make_pair("minus", this->minus), std::make_pair("multiply", this->multiply),
        std::make_pair("divide", this->divide), std::make_pair("equal", this->equal), std::make_pair("erase", this->erase),
        std::make_pair("dot", this->dot), std::make_pair("negate", this->negate), std::make_pair("ce", this->ce),
        std::make_pair("c", this->c), std::make_pair("percent", this->percent), std::make_pair("sqrt", this->sqrt),
        std::make_pair("sqr", this->sqr), std::make_pair("inverse", this->inv)
    }))
{}

GeneralCalculator::~GeneralCalculator(){}

void GeneralCalculator::setup(){
    SETUP_CAL_UI(contentUi, MainWindow)
    auto allButtons = MainWindow->findChildren<QPushButton*>();
    foreach(QPushButton* button, allButtons){
        connect(button, SIGNAL(clicked()), this, SLOT(buttonPushed()));
    }
}

void GeneralCalculator::buttonPushed(){
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

void GeneralCalculator::calculate(){
    if(this->getInter().isEmpty())
        return;
    else{
        if(this->isBracketUnclosed()){
            this->closeAllBracket();
            this->setResult(calculateExpr(this->getInter()));
        }
        else{
            if(this->endsWithBracket())
                this->setResult(calculateExpr(this->getInter()));
            else
                this->setResult(calculateExpr(this->getInter() + " " + this->getResult()));
        }
    }
    this->setInter("");
    this->calculated = true;
}

void GeneralCalculator::calculate(const QString &op){
    QString &&result = this->getResult();
    if(this->getInter().isEmpty()) return;
    else{
        if(this->endsWithBracket()){
            this->setResult(calculateExpr(this->getInter()));
            this->appendInter(op);
        }
        else{
            this->setResult(calculateExpr(this->getInter() + " " + this->getResult()));
            this->appendInter(result);
            this->appendInter(op);
        }
    }
    this->calculated = true;
}

void GeneralCalculator::arithmetic(const QString &op){
    if(this->getInter().isEmpty()){
        this->setInter(this->getResult() + " " + op);
        this->calculated = true;
    }
    else if(this->calculated){
        if(this->lastOp() == op)
            return;
        else{
            if(this->isLastOpArithmetic())
                this->replaceLastOp(op);
            else
                this->appendInter(op);
        }
    }
    else{
        if(this->isLastOpArithmetic() || !this->specialStart)
            this->calculate(op);
        else{
            this->replaceLastOp(op);
            this->specialStart = false;
            this->calculated = true;
        }
    }
}
void GeneralCalculator::plus(){
    this->arithmetic(Operator::Normal::plus);
}

void GeneralCalculator::minus(){
    this->arithmetic(Operator::Normal::minus);
}

void GeneralCalculator::multiply(){
    this->arithmetic(Operator::Normal::mult);
}

void GeneralCalculator::divide(){
    this->arithmetic(Operator::Normal::divide);
}

void GeneralCalculator::equal(){
    this->calculate();
}

void GeneralCalculator::erase(){
    if(!this->getResult().isEmpty() && !this->calculated){
        this->chopResult(1);
    }
}

void GeneralCalculator::dot(){
    if(this->calculated)
        this->setResult("0.");
    else{
        if(this->getResult().indexOf(".") == -1)
            this->appendResult(".");
    }
}

void GeneralCalculator::negate(){
    QString &&result = this->getResult(false);
    if(result == "0") return;
    if(this->calculated)
        this->unarySpecial(Operator::Special::negate);
    else{
        if(result.front() == '-'){
            this->removeResult(1);
        }
        else
            this->prependResult("-");
    }
}

void GeneralCalculator::ce(){
    this->setResult("");
    this->calculated = false;
}

void GeneralCalculator::c(){
    this->setResult("");
    this->setInter("");
    this->calculated = false;
}

void GeneralCalculator::percent(){
    double result = calculateExpr(this->chopInterOp(1)).toDouble() * this->getResult().toDouble() / 100;
    QString &&str = QString::fromStdString(doubleToString(result));
    this->appendInter(str);
    this->setResult(str);
    this->calculated = true;
}

void GeneralCalculator::unarySpecial(const QString &op){
    if(this->getInter().isEmpty() || !this->calculated || this->isLastOpArithmetic()){
        QString &&expr = QString("%1(%2)").arg(op).arg(this->getResult());
        this->appendInter(expr);
        this->setResult(calculateExpr(expr));
        this->calculated = true;
    }
    else{
        QString &&expr = QString("%1(%2)").arg(op).arg(this->lastOp());
        this->replaceLastOp(expr);
        this->setResult(calculateExpr(expr));
    }
}


void GeneralCalculator::sqrt(){
    this->unarySpecial(Operator::Special::sqrt);
}

void GeneralCalculator::sqr(){
    this->unarySpecial(Operator::Special::sqr);
}

void GeneralCalculator::inv(){
    this->unarySpecial(Operator::Special::inv);
}
