#include "mainwindow.h"
#include "calculator.h"

void MainWindow::addNumber(const QString &str){
    if(this->calculated){
        this->setResult(str);
        this->calculated = false;
    }
    else{
        if(this->getResult() == "0"){
            if(str == "0")
                return;
            else{
                this->setResult(str);
            }
        }
        else{
            this->setResult(this->getResult() + str);
        }
    }
}

void MainWindow::calculate(){
    this->setResult(calculateExpr(this->getInter() + " " + this->getResult()));
}

void MainWindow::arithmetic(const QString &op){
    if(this->calculated){
        if(this->lastOp() == op)
            return;
        else
            if(this->isLastOpArithmetic())
                this->replaceLastOp(op);
            else
                this->setInter(this->getInter() + " " + op);
    }
    else{
        this->calculated = true;
        if(this->getInter() == ""){
            this->setInter(this->getResult() + " " + op);
        }
        else{
            QString result = this->getResult();
            this->calculate();
            this->setInter(this->getInter() + " " + result + " " + op);
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
