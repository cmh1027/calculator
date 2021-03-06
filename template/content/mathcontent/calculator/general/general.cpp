#include <QString>
#include <QtCore/QRegExp>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include "general.h"
#include "ui_general.h"
#include "../../../../../module/mathcontent/operator.h"
#include "../../../../../module/mathcontent/calculation.h"
#include "../../../../../module/utility.h"
#include "../../../../mainwindow.h"
namespace Template{
    GeneralCalculator::GeneralCalculator(MainWindow* window) :
        Template::Calculator(window), contentUi(new Ui::GeneralCalculator),
        contentWidget(this->findChild<QWidget*>("buttonWidget"))
    {
         Operators["plus"] = this->plus;
         Operators["minus"] = this->minus;
         Operators["multiply"] = this->multiply;
         Operators["divide"] = this->divide;
         Operators["equal"] = this->equal;
         Operators["erase"] = this->erase;
         Operators["dot"] = this->dot;
         Operators["negate"] = this->negate;
         Operators["ce"] = this->ce;
         Operators["c"] = this->c;
         Operators["percent"] = this->percent;
         Operators["sqrt"] = this->sqrt;
         Operators["sqr"] = this->sqr;
         Operators["inverse"] = this->inverse;
         Operators["leftBracket"] = this->leftBracket;
         Operators["rightBracket"] = this->rightBracket;
    }

    GeneralCalculator::~GeneralCalculator(){
        delete this->contentUi;
    }

    void GeneralCalculator::setup(){
        this->setupUi(this, this->contentUi, this->contentWidget);
        this->installMenu();
    }

    void GeneralCalculator::buttonConnect(){
        foreach(QPushButton* button, contentWidget->findChildren<QPushButton*>()){
            connect(button, &QPushButton::clicked, this, &this->buttonPushed);
        }
    }


    void GeneralCalculator::buttonPushed(){
        if(this->isModifying)
            return;
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
                Q_ASSERT(this->Operators.contains(funcName));
            }
        }
    }

    void GeneralCalculator::refresh(){
        this->setInter(this->getInter());
        this->calculateAgain();
    }

    void GeneralCalculator::calculateAgain(){
        if(!this->getInter().isEmpty()){
            if(this->isLastOpOperator())
                this->setResult(calculateExpression(this->chopInterOp(1)));
            else
                this->setResult(calculateExpression(this->getInter()));
        }
    }

    QString GeneralCalculator::calculateExpression(QString expr){
        while(this->isBracketUnclosed(expr))
            expr = expr + " )";
        return Calculation::calculateExpr(expr, this->doubleList);
    }

    void GeneralCalculator::calculate(){
        if(this->getInter().isEmpty())
            return;
        else{
            if(this->isBracketUnclosed()){
                this->closeAllBracket();
                this->setResult(calculateExpression(this->getInter()));
            }
            else{
                if(this->endWithBracket())
                    this->setResult(calculateExpression(this->getInter()));
                else
                    this->setResult(calculateExpression(this->getInter() + " " + this->getResult()));
            }
        }
        this->setInter("");
        this->calculated = true;
    }

    void GeneralCalculator::calculate(const QString &op){
        QString &&result = this->getResult();
        if(this->getInter().isEmpty()) return;
        else{
            if(this->endWithBracket()){
                this->setResult(calculateExpression(this->getInter()));
                this->appendInter(op);
            }
            else{
                this->setResult(calculateExpression(this->getInter() + " " + this->getResult()));
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
        this->clearDoubleListEqual();
    }

    void GeneralCalculator::erase(){
        if(!this->getResult().isEmpty() && !this->calculated){
            this->chopResult(1);
        }
        else{
            this->setResult("0");
        }
    }

    void GeneralCalculator::dot(){
        if(this->calculated){
            if(!this->getInter().isEmpty() && !this->isLastOpArithmetic() && this->lastOp() != Operator::Normal::leftBracket)
                this->setInter(this->chopInterOp(1));
            this->setResult("0.");
            this->calculated = false;
        }
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
        this->setResult("0");
        this->calculated = false;
    }

    void GeneralCalculator::c(){
        this->setResult("0");
        this->setInter("");
        this->clearDoubleList();
        this->calculated = false;
    }

    void GeneralCalculator::percent(){
        double result = calculateExpression(this->chopInterOp(1)).toDouble() * this->getResult().toDouble() / 100;
        QString &&str = Utility::doubleToString(result);
        this->appendInter(str);
        this->setResult(str);
        this->calculated = true;
    }

    void GeneralCalculator::unarySpecial(const QString &op){
        if(this->getInter().isEmpty() || !this->calculated || this->isLastOpArithmetic()){
            QString &&expr = QString("%1(%2)").arg(op).arg(this->getResult());
            this->appendInter(expr);
            this->setResult(calculateExpression(expr));
            this->calculated = true;
        }
        else{
            QString &&lastOp = this->lastOp();
            if(this->startWithBracket(lastOp) && this->endWithBracket(lastOp)){
                QString &&expr = QString("%1%2").arg(op).arg(this->lastOp());
                this->replaceLastOp(expr);
                this->setResult(calculateExpression(expr));
            }
            else{
                QString &&expr = QString("%1(%2)").arg(op).arg(this->lastOp());
                this->replaceLastOp(expr);
                this->setResult(calculateExpression(expr));
            }
        }
    }


    void GeneralCalculator::sqrt(){
        this->unarySpecial(Operator::Special::sqrt);
    }

    void GeneralCalculator::sqr(){
        this->unarySpecial(Operator::Special::sqr);
    }

    void GeneralCalculator::inverse(){
        this->unarySpecial(Operator::Special::inv);
    }

    void GeneralCalculator::leftBracket(){
        if(this->calculated){
            this->setResult("0");
            this->appendInter(Operator::Normal::leftBracket);
        }
        else{
            this->appendInter(Operator::Normal::leftBracket);
            this->calculated = true;
        }
    }

    void GeneralCalculator::rightBracket(){
        if(this->isBracketUnclosed()){
            if(this->isLastOpArithmetic())
                this->appendInter(this->getResult());
            this->appendInter(Operator::Normal::rightBracket);
        }
        this->setResult(calculateExpression(this->getInter()));
        this->calculated = true;
    }

    void GeneralCalculator::disableLineEdit(){
        Calculator::disableLineEdit();
        this->calculateAgain();
    }

    void GeneralCalculator::mousePressEvent(QMouseEvent*){
        if(this->findChild<QLabel*>("interLabel")->underMouse())
            this->enableLineEdit();
        else if(this->findChild<QLineEdit*>("interLineEdit")->isVisible() && \
                !this->findChild<QLineEdit*>("interLineEdit")->underMouse())
            this->disableLineEdit();
    }

}
