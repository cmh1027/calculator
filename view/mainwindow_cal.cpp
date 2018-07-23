#include "mainwindow.h"
#include "calculator.h"

void MainWindow::addNumber(const QString &str){
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

void MainWindow::calculate(){
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

void MainWindow::calculate(const QString &op){
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

void MainWindow::arithmetic(const QString &op){
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
void MainWindow::plus(){
    this->arithmetic("+");
}

void MainWindow::minus(){
    this->arithmetic("-");
}

void MainWindow::multiply(){
    this->arithmetic("×");
}

void MainWindow::divide(){
    this->arithmetic("÷");
}

void MainWindow::equal(){
    this->calculate();
}

void MainWindow::erase(){
    if(!this->getResult().isEmpty() && !this->calculated){
        this->chopResult(1);
    }
}

void MainWindow::dot(){
    if(this->calculated)
        this->setResult("0.");
    else{
        if(this->getResult().indexOf(".") == -1)
            this->appendResult(".");
    }
}

void MainWindow::negate(){
    QString &&result = this->getResult(false);
    if(result == "0") return;
    if(result.front() == '-'){
        this->removeResult(1);
    }
    else
        this->prependResult("-");
}

void MainWindow::ce(){
    this->setResult("");
    this->calculated = false;
}

void MainWindow::c(){
    this->setResult("");
    this->setInter("");
    this->calculated = false;
}

void MainWindow::percent(){
    double result = calculateExpr(this->chopInterOp(1)).toDouble() * this->getResult().toDouble() / 100;
    QString &&str = QString::fromStdString(doubleToString(result));
    this->appendInter(str);
    this->setResult(str);
    this->calculated = true;
}

void MainWindow::unarySpecial(const QString &op){
    if(this->getInter().isEmpty() || !this->calculated){
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

void MainWindow::binarySpecial(const QString &op){
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
}

void MainWindow::sqrt(){
    this->unarySpecial("sqrt");
}

void MainWindow::sqr(){
    this->unarySpecial("sqr");
}

void MainWindow::inv(){
    this->unarySpecial("inv");
}

void MainWindow::root(){
    this->binarySpecial("root");
}

void MainWindow::pow(){
    this->binarySpecial("^");
}


