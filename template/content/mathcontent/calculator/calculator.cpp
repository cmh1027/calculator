#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QString>
#include "calculator.h"
#include "ui_calculator.h"
#include "../../../mainwindow.h"
#include "../../../../module/calculator/operator.h"
#include "../../../../module/utility.h"
#include "../../../../config/config.h"
#include "../../../../module/exception.h"
#include "menu/constmenulayout.h"
#include "menu/funcmenulayout.h"

extern Configuration* config;
namespace Template{
    Calculator::Calculator(MainWindow* window) : Template::MathContent(window),
        contentUi(new Ui::Calculator), contentWidget(this),
        calculated(false), specialStart(false), result("0"), isModifying(false)
    {
        contentUi->setupUi(this);
        this->resultLabel = contentWidget->findChild<QLabel*>("resultLabel");
        this->interLabel = contentWidget->findChild<QLabel*>("interLabel");
        this->interLineEdit = contentWidget->findChild<QLineEdit*>("interLineEdit");
        this->interLineEdit->hide();
        this->setResult(this->result);
    }

    Calculator::~Calculator(){
        delete this->contentUi;
    }

    void Calculator::installMenu(){
        this->install<ConstMenuLayout, Template::Calculator>("constMenuScrollArea", this->findChild<QPushButton*>("constButton"));
        this->install<FuncMenuLayout, Template::Calculator>("funcMenuScrollArea", this->findChild<QPushButton*>("functionButton"));
    }



    QString Calculator::getResult(const bool &chopDot){
        if(chopDot && this->result != ""){
            if(this->result.back() == "."){
                this->setResult(this->result.chopped(1));
            }
        }
        return this->result;
    }

    void Calculator::setResult(const QString &str){
        this->result = str.trimmed();
        try{
            this->resultLabel->setText(Utility::transformExpr(str.trimmed(), this->doubleList));
        }
        catch(std::InvalidExprException &e){
            this->resultLabel->setText(e.what());
        }
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

    QString Calculator::getInter() const{
        return this->inter;
    }

    void Calculator::setInter(const QString &str){
        this->inter = str.trimmed();
        try{
            this->interLabel->setText(Utility::transformExpr(str.trimmed(), this->doubleList));
        }
        catch(std::InvalidExprException &e){
            this->resultLabel->setText(e.what());
        }
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
        for(int i=0; i<num; ++i){
            inter.chop(this->lastOp(inter).length());
            inter.trimmed();
        }
        return inter;
    }

    QString Calculator::lastOp(const QString &str) const{
        if(str.isEmpty())
            return "";
        QChar lastChar = str.back();
        int i;
        if(lastChar == Operator::Normal::rightBracket){
            int bracketNum = 0;
            for(i = str.length()-1; i >= 0; --i){
                if(str.at(i) == Operator::Normal::rightBracket)
                    ++bracketNum;
                else if(str.at(i) == Operator::Normal::leftBracket)
                    --bracketNum;
                if(bracketNum == 0)
                    break;
            }
            for(i -= 1; i >=0 ; --i){
                if(!(str.at(i).isLower() || str.at(i).isUpper())){
                    ++i;
                    break;
                }
            }
        }
        else if(lastChar.isDigit()){
            for(i = str.length()-1; i >= 0; --i){
                if(!str.at(i).isDigit())
                    break;
            }
        }
        else if(lastChar == "}"){
            for(i = str.length()-1; i >= 0; --i){
                if(str.at(i) == "{")
                    break;
            }
        }
        else{
            for(i = str.length()-1; i >= 0; --i){
                if(!(str.at(i).isUpper() || str.at(i).isLower()))
                    break;
            }
        }
        return str.mid(i);
    }

    QString Calculator::lastOp() const{
        QString&& str = this->getInter();
        if(str.isEmpty())
            return "";
        QChar lastChar = str.back();
        int i;
        if(lastChar == Operator::Normal::rightBracket){
            int bracketNum = 0;
            for(i = str.length()-1; i >= 0; --i){
                if(str.at(i) == Operator::Normal::rightBracket)
                    ++bracketNum;
                else if(str.at(i) == Operator::Normal::leftBracket)
                    --bracketNum;
                if(bracketNum == 0)
                    break;
            }
            for(i -= 1; i >=0 ; --i){
                if(!(str.at(i).isLower() || str.at(i).isUpper())){
                    ++i;
                    break;
                }
            }
        }
        else if(lastChar.isDigit()){
            for(i = str.length()-1; i >= 0; --i){
                if(!str.at(i).isDigit())
                    break;
            }
        }
        else if(lastChar == "}"){
            for(i = str.length()-1; i >= 0; --i){
                if(str.at(i) == "{")
                    break;
            }
        }
        else{
            for(i = str.length()-1; i >= 0; --i){
                if(!(str.at(i).isUpper() || str.at(i).isLower()))
                    break;
            }
        }
        return str.mid(i);
    }

    bool Calculator::isLastOpArithmetic() const{
        QString&& op = this->lastOp();
        return op == Operator::Normal::plus || op == Operator::Normal::minus || op == Operator::Normal::mult ||
               op == Operator::Normal::divide || op == Operator::Normal::altMult || op == Operator::Normal::altDivide;
    }

    bool Calculator::isLastOpOperator() const{
        QString&& op = this->lastOp();
        bool isDouble;
        op.toDouble(&isDouble);
        return !(isDouble || (op.indexOf("{") != -1 && op.indexOf("}") != -1) ||
               (op.indexOf("(") != -1 && op.indexOf(")") != -1));
    }

    void Calculator::replaceLastOp(const QString &expr){
        QString&& inter = this->getInter();
        QString&& lastOp = this->lastOp();
        if(inter == lastOp)
            this->setInter(expr);
        else
            this->setInter(inter.replace(inter.indexOf(lastOp), inter.length(), expr));
    }

    bool Calculator::isBracketUnclosed() const{
        return this->getInter().count(Operator::Normal::leftBracket) > this->getInter().count(Operator::Normal::rightBracket);
    }

    bool Calculator::isBracketUnclosed(const QString &expr) const{
        return expr.count(Operator::Normal::leftBracket) > expr.count(Operator::Normal::rightBracket);
    }

    bool Calculator::startWithBracket(const QString &expr) const{
        return expr.startsWith(Operator::Normal::leftBracket);
    }

    bool Calculator::endWithBracket(const QString &expr) const{
        return expr.endsWith(Operator::Normal::rightBracket);
    }

    bool Calculator::endWithBracket() const{
        return this->getInter().endsWith(Operator::Normal::rightBracket);
    }

    void Calculator::closeAllBracket(){
        this->appendInter(this->getResult(), false);
        while(this->isBracketUnclosed())
            this->appendInter(Operator::Normal::rightBracket);
    }

    void Calculator::addNumber(const QString &str){
        if(this->calculated){
            if(!this->getInter().isEmpty() && !this->isLastOpArithmetic() && this->lastOp() != Operator::Normal::leftBracket)
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

    void Calculator::constant(const QString &constant){
        this->setResult(QString("%1").arg(constant));
        this->calculated = true;
    }

    void Calculator::changeButton(const QString &targetName, const QString &buttonName, const QString &icon){
        QPushButton *button;
        if(targetName.indexOf("Button") != 0)
            button = this->contentWidget->findChild<QPushButton*>(targetName+"Button");
        else
            button = this->contentWidget->findChild<QPushButton*>(targetName);
        if(buttonName.indexOf("Button") != 0)
            button->setObjectName(buttonName+"Button");
        else
            button->setObjectName(buttonName);
        button->setText(icon);
    }

    void Calculator::clearDoubleList(){
        for(auto it = doubleList.begin(); it != doubleList.end();){
            if((*it).isDefault())
                ++it;
            else
                it = doubleList.erase(it);
        }
    }

    void Calculator::precisionChanged(){
        this->setInter(this->getInter());
        this->setResult(this->getResult());
    }

    void Calculator::enableLineEdit(){
        this->isModifying = true;
        this->interLineEdit->setText(this->inter);
        this->interLabel->hide();
        this->interLineEdit->show();
    }

    void Calculator::disableLineEdit(){
        this->isModifying = false;
        this->setInter(this->interLineEdit->text());
        this->interLineEdit->hide();
        this->interLabel->show();
    }
}
