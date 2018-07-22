#include "mainwindow.h"
#include "calculator.h"

void MainWindow::addNumber(const QString &str){
    if(this->calculated){
        if(!this->isLastOpArithmetic() &&  !this->isLastOpOpenedSpecial())
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
    this->calculated = true;
}

void MainWindow::arithmetic(const QString &op){
    if(this->calculated){
        if(this->lastOp() == op)
            return;
        else
            if(this->isLastOpArithmetic())
                this->replaceLastOp(op);
            else if(this->isLastOpOpenedSpecial()){
                this->specialToArithmetic(op);
            }
            else{
                this->appendInter(op);
            }
    }
    else{
        if(this->getInter().isEmpty()){
            this->setInter(this->getResult() + " " + op);
            this->calculated = true;
        }
        else if(this->isLastOpArithmetic()){
            this->calculate(op);
        }
        else if(this->isLastOpOpenedSpecial()){
            this->closeAllSpecial();
            this->calculate(op);
        }
        else{
            std::cout << "Unexpected Condition!\n";
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

void MainWindow::unarySpecial(const QString &format){
    if(this->calculated){
       QString &&expr = QString(format).arg(this->lastOp());
       this->replaceLastOp(expr);
       this->setResult(calculateExpr(expr));
   }
   else{
       QString &&expr = QString(format).arg(this->getResult());
       this->appendInter(expr);
       this->setResult(calculateExpr(expr));
       this->calculated = true;
   }
}

void MainWindow::binarySpecial(const QString &format){
    // pow(pow(3, 3),
    // mod
    if(this->calculated){
        if(this->isLastOpArithmetic()){
            this->arithmeticToSpecial(format);
        }
        else{
            this->appendInter(QString("%1(%2,").arg(format).arg(this->lastOp()));
        }
    }
    else{
        if(this->isLastOpOpenedSpecial())
            this->replaceLastOp(QString("%1(%2%3),").arg(format).arg(this->lastOp()).arg(this->getResult()));
        else
            this->appendInter(QString("%1(%2,").arg(format).arg(this->getResult()));
        this->calculated = true;
    }
}

void MainWindow::sqrt(){
    this->unarySpecial("root(%1,2)");
}

void MainWindow::sqr(){
    this->unarySpecial("pow(%1,2)");
}

void MainWindow::inv(){
    this->unarySpecial("inv(%1)");
}

void MainWindow::root(){
    this->binarySpecial("root");
}

void MainWindow::pow(){
    this->binarySpecial("pow");
}


