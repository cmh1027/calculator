#include "mainwindow.h"
#include "calculator.h"

void MainWindow::addNumber(const QString &str){
    if(this->calculated){
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
            this->appendResult(str);
        }
    }
}

void MainWindow::calculate(){
    if(this->getInter().isEmpty())
        this->setResult(calculateExpr(this->getResult()));
    else{
        if(this->isLastOpOpenedSpecial()){
            this->closeAllSpecial();
            this->setResult(calculateExpr(this->getInter()));
        }
        else{
            if(this->isLastOpArithmetic())
                this->setResult(calculateExpr(this->getInter() + " " + this->getResult()));
            else
                this->setResult(calculateExpr(this->getInter()));
        }
    }
    this->setInter("");
    this->calculated = true;
}

void MainWindow::calculate(const QString &op){
    QString &&result = this->getResult();
    if(this->getInter().isEmpty()) return;
    else{
        if(this->isLastOpOpenedSpecial()){
            this->closeAllSpecial();
            this->setResult(calculateExpr(this->getInter()));
            this->appendInter(op);
        }
        else{
            if(this->isLastOpArithmetic()){
                this->setResult(calculateExpr(this->getInter() + " " + this->getResult()));
                this->appendInter(result);
                this->appendInter(op);
            }
            else{
                this->setResult(calculateExpr(this->getInter()));
                this->appendInter(op);
            }
        }
    }
    this->calculated = true;
}

void MainWindow::arithmetic(const QString &op){
    if(this->calculated){
        if(this->lastOp() == op)
            return;
        else
            if(this->isLastOpArithmetic())
                this->replaceLastOp(op);
            else
                this->appendInter(op);
    }
    else{
        if(this->isLastOpArithmetic()){
            this->calculated = true;
            if(this->getInter().isEmpty()){
                this->setInter(this->getResult() + " " + op);
            }
            else{
                this->calculate(op);
            }
        }
        else{
            this->specialToArithmetic(op);
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
    if(!this->calculated) this->calculate();
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

void MainWindow::sqrt(){
    if(this->calculated){
        QString &&expr = std::move(QString("root(%1,2)").arg(this->lastOp()));
        this->replaceLastOp(expr);
        this->setResult(this->getInter());
    }
    else{
        QString &&expr = std::move(QString("root(%1,2)").arg(this->getResult()));
        this->appendInter(expr);
        this->setResult(calculateExpr(expr));
        this->calculated = true;
    }
}

void MainWindow::sqr(){
    QString &&expr = std::move(QString("pow(%1,2)").arg(this->getResult()));
    this->appendInter(expr);
    this->setResult(calculateExpr(expr));
    this->calculated = true;
}

void MainWindow::inv(){
    QString &&expr = std::move(QString("inv(%1)").arg(this->getResult()));
    this->appendInter(expr);
    this->setResult(calculateExpr(expr));
    this->calculated = true;
}

void MainWindow::root(){
    QString &&expr = std::move(QString("inv(%1)").arg(this->getResult()));
    this->appendInter(expr);
    this->setResult(calculateExpr(expr));
    this->calculated = true;
}

void MainWindow::pow(){

}


