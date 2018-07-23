
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    Operators(std::initializer_list<std::pair<QString, void(MainWindow::*)()>>({
        std::make_pair("plus", this->plus), std::make_pair("minus", this->minus), std::make_pair("multiply", this->multiply),
        std::make_pair("divide", this->divide), std::make_pair("equal", this->equal), std::make_pair("erase", this->erase),
        std::make_pair("dot", this->dot), std::make_pair("negate", this->negate), std::make_pair("ce", this->ce),
        std::make_pair("c", this->c), std::make_pair("percent", this->percent), std::make_pair("sqrt", this->sqrt),
        std::make_pair("sqr", this->sqr), std::make_pair("inverse", this->inv), std::make_pair("pow", this->pow),
        std::make_pair("root", this->root)
    }))
{
    ui->setupUi(this);
    QPushButton* button;
    auto allButtons = this->findChildren<QPushButton*>();
    foreach(button, allButtons){
        connect(button, SIGNAL(clicked()), this, SLOT(buttonPushed()));
    }
    this->interLabel = this->findChild<QLabel*>("intermediateLabel");
    this->resultLabel = this->findChild<QLabel*>("resultLabel");
    this->calculated = false;
    this->specialStart = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buttonPushed(){
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

QString MainWindow::getResult(const bool &chopDot){
    QString &&result = this->resultLabel->text();
    if(chopDot){
        if(result.back() == '.'){
            this->setResult(result.chopped(1));
        }
    }
    return result;
}

void MainWindow::appendResult(const QString &str){
    this->setResult(this->getResult(false)+str);
}

void MainWindow::prependResult(const QString &str){
    this->setResult(str + this->getResult(false));
}

void MainWindow::chopResult(const int &num){
    this->setResult(this->getResult(false).chopped(num));
}

void MainWindow::removeResult(const int &num){
    this->setResult(this->getResult(false).remove(0, num));
}

void MainWindow::removeResult(const int &pos, const int &num){
    this->setResult(this->getResult(false).remove(pos, num));
}

void MainWindow::setResult(const QString &str){
    this->resultLabel->setText(str);
}

QString MainWindow::getInter() const{
    return this->interLabel->text();
}

void MainWindow::appendInter(const QString &str, const bool &autoSpace){
    if(this->getInter().isEmpty())
        this->setInter(str);
    else{
        if(autoSpace)
            this->setInter(this->getInter() + " " + str);
        else
            this->setInter(this->getInter() + str);
    }
}

void MainWindow::prependInter(const QString &str, const bool &autoSpace){
    if(this->getInter().isEmpty())
        this->setInter(str);
    else{
        if(autoSpace)
            this->setInter(str + " " + this->getInter());
        else
            this->setInter(str + this->getInter());
    }
}

void MainWindow::chopInter(const int &num){
    this->setInter(this->getInter().chopped(num));
}

void MainWindow::removeInter(const int &num){
    this->setResult(this->getInter().remove(0, num));
}

void MainWindow::removeInter(const int &pos, const int &num){
    this->setResult(this->getInter().remove(pos, num));
}

QString MainWindow::chopInterOp(const int &num){
    QString&& inter = this->getInter();
    int index;
    for(int i=0; i<num; ++i){
        if((index = inter.lastIndexOf(" ")) == -1)
            return "";
        inter.chop(inter.length() - index);
    }
    return inter;
}

QString MainWindow::removeInterOp(const int &num){
    QString&& inter = this->getInter();
    int index;
    for(int i=0; i<num; ++i)
        if((index = inter.indexOf(" ")) == -1)
            return "";
        inter = inter.remove(0, inter.indexOf(" ") + 1);
    return inter;
}

void MainWindow::setInter(const QString &str){
    this->interLabel->setText(str);
}

QString MainWindow::lastOp() const{
    QString&& inter = this->getInter();
    int lastIndex;
    if((lastIndex = inter.lastIndexOf(" ")) == -1)
        return inter;
    else
        return inter.remove(0, lastIndex+1);
}

bool MainWindow::isLastOpArithmetic() const{
    QString&& op = this->lastOp();
    return op == Operator::Normal::plus || op == Operator::Normal::minus || op == Operator::Normal::mult ||
           op == Operator::Normal::divide || op == Operator::Normal::altMult || op == Operator::Normal::altDivide;
}

void MainWindow::replaceLastOp(const QString &str){
    QString&& expr = this->getInter();
    if(expr.lastIndexOf(" ") == -1)
        this->setInter(str);
    else
        this->setInter(expr.replace(expr.lastIndexOf(" ")+1, expr.length(), str));
}

bool MainWindow::isBracketUnclosed() const{
    return this->getInter().count(Operator::Normal::leftBracket) > this->getInter().count(Operator::Normal::rightBracket);
}

bool MainWindow::endsWithBracket() const{
    return this->getInter().endsWith(Operator::Normal::rightBracket);
}

void MainWindow::closeAllBracket(){
    this->appendInter(this->getResult(), false);
    while(this->isBracketUnclosed())
        this->appendInter(Operator::Normal::rightBracket);
}
