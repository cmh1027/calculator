#include "calculator.h"

Calculator::Calculator(QMainWindow *window) : MainWindow(window), calculated(false), specialStart(false){}

Calculator::~Calculator(){}

void Calculator::bindLabels(){
    resultLabel = MainWindow->findChild<QLabel*>("resultLabel");
    interLabel = MainWindow->findChild<QLabel*>("intermediateLabel");
}

QString Calculator::getResult(const bool &chopDot){
    QString &&result = this->resultLabel->text();
    if(chopDot){
        if(result.back() == '.'){
            this->setResult(result.chopped(1));
        }
    }
    return result;
}

void Calculator::appendResult(const QString &str){
    this->setResult(this->getResult(false)+str);
}

void Calculator::prependResult(const QString &str){
    this->setResult(str + this->getResult(false));
}

void Calculator::chopResult(const int &num){
    this->setResult(this->getResult(false).chopped(num));
}

void Calculator::removeResult(const int &num){
    this->setResult(this->getResult(false).remove(0, num));
}

void Calculator::removeResult(const int &pos, const int &num){
    this->setResult(this->getResult(false).remove(pos, num));
}

void Calculator::setResult(const QString &str){
    this->resultLabel->setText(str);
}

QString Calculator::getInter() const{
    return this->interLabel->text();
}

void Calculator::appendInter(const QString &str, const bool &autoSpace){
    if(this->getInter().isEmpty())
        this->setInter(str);
    else{
        if(autoSpace)
            this->setInter(this->getInter() + " " + str);
        else
            this->setInter(this->getInter() + str);
    }
}

void Calculator::prependInter(const QString &str, const bool &autoSpace){
    if(this->getInter().isEmpty())
        this->setInter(str);
    else{
        if(autoSpace)
            this->setInter(str + " " + this->getInter());
        else
            this->setInter(str + this->getInter());
    }
}

void Calculator::chopInter(const int &num){
    this->setInter(this->getInter().chopped(num));
}

void Calculator::removeInter(const int &num){
    this->setResult(this->getInter().remove(0, num));
}

void Calculator::removeInter(const int &pos, const int &num){
    this->setResult(this->getInter().remove(pos, num));
}

QString Calculator::chopInterOp(const int &num){
    QString&& inter = this->getInter();
    int index;
    for(int i=0; i<num; ++i){
        if((index = inter.lastIndexOf(" ")) == -1)
            return "";
        inter.chop(inter.length() - index);
    }
    return inter;
}

QString Calculator::removeInterOp(const int &num){
    QString&& inter = this->getInter();
    int index;
    for(int i=0; i<num; ++i)
        if((index = inter.indexOf(" ")) == -1)
            return "";
        inter = inter.remove(0, inter.indexOf(" ") + 1);
    return inter;
}

void Calculator::setInter(const QString &str){
    this->interLabel->setText(str);
}

QString Calculator::lastOp() const{
    QString&& inter = this->getInter();
    int lastIndex;
    if((lastIndex = inter.lastIndexOf(" ")) == -1)
        return inter;
    else
        return inter.remove(0, lastIndex+1);
}

bool Calculator::isLastOpArithmetic() const{
    QString&& op = this->lastOp();
    return op == Operator::Normal::plus || op == Operator::Normal::minus || op == Operator::Normal::mult ||
           op == Operator::Normal::divide || op == Operator::Normal::altMult || op == Operator::Normal::altDivide;
}

void Calculator::replaceLastOp(const QString &str){
    QString&& expr = this->getInter();
    if(expr.lastIndexOf(" ") == -1)
        this->setInter(str);
    else
        this->setInter(expr.replace(expr.lastIndexOf(" ")+1, expr.length(), str));
}

bool Calculator::isBracketUnclosed() const{
    return this->getInter().count(Operator::Normal::leftBracket) > this->getInter().count(Operator::Normal::rightBracket);
}

bool Calculator::endsWithBracket() const{
    return this->getInter().endsWith(Operator::Normal::rightBracket);
}

void Calculator::closeAllBracket(){
    this->appendInter(this->getResult(), false);
    while(this->isBracketUnclosed())
        this->appendInter(Operator::Normal::rightBracket);
}

void Calculator::addNumber(const QString &str){
    if(this->calculated){
        if(!this->getInter().isEmpty() && !this->isLastOpArithmetic())
            this->setInter(this->chopInterOp(1));
        this->setResult(str);
        this->calculated = false;
    }
    else{
        if(this->getResult(false) == "0"){
            if(str == "0")
                return;
            else{
                this->setResult(str);
            }
        }
        else{
            if(this->specialStart){
                this->setResult(str);
                this->specialStart = false;
            }
            else
                this->appendResult(str);
        }
    }
}