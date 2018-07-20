#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    Operators(std::initializer_list<std::pair<QString, void(MainWindow::*)()>>({
    std::make_pair("plus", this->plus), std::make_pair("minus", this->minus), std::make_pair("multiply", this->multiply),
    std::make_pair("divide", this->divide)
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
        buttonName.chop(6); // Button
        QString funcName = buttonName;
        if(this->Operators.contains(funcName))
            (this->*(this->Operators[funcName]))();
        else{
            std::cout << "Does not contain : " << funcName.toStdString() << "\n";
        }
    }
}

QString MainWindow::getResult() const{
    return this->resultLabel->text();
}

void MainWindow::addResult(const QString &str){
    this->setResult(this->getResult()+str);
}


void MainWindow::setResult(const QString &str){
    this->resultLabel->setText(str);
}

QString MainWindow::getInter() const{
    return this->interLabel->text();
}

void MainWindow::addInter(const QString &str){
    this->setInter(this->getResult() + " " + str);
}

void MainWindow::setInter(const QString &str){
    this->interLabel->setText(str);
}

QString MainWindow::lastOp() const{
    QString inter = this->getInter();
    int lastIndex;
    if((lastIndex = inter.lastIndexOf(" ")) == -1)
        return QString("");
    else
        return inter.remove(0, lastIndex+1);
}

bool MainWindow::isLastOpArithmetic() const{
    QString op = this->lastOp();
    return op == "+" || op == "-" || op == "×" || op == "÷";
}

void MainWindow::replaceLastOp(const QString &str){
    QString expr = this->getInter();
    this->setInter(expr.replace(expr.lastIndexOf(" ")+1, 1, str));
}
