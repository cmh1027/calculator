#include "mainwindow.h"
#include "../include.h"
#include "ui_mainwindow.h"
#include "calculator.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QLabel *q = this->findChild<QLabel*>("intermediateLabel");
    QString a = "log(-1)";
    q->setText(calculate(a));
}

MainWindow::~MainWindow()
{
    delete ui;
}
