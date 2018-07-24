#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow() :
    mainWindowUi(new Ui::MainWindow), content(nullptr)
{
    mainWindowUi->setupUi(this);
    this->generalCalculator();
}

MainWindow::~MainWindow()
{
    delete mainWindowUi;
    delete content;
}


void MainWindow::generalCalculator(){
    RENDER(GeneralCalculator)
}

void MainWindow::buttonPushed(){
    std::cout << "Test\n";
}
