#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow() :
    mainWindowUi(new Ui::MainWindow), content(nullptr)
{
    mainWindowUi->setupUi(this);
    this->generalCalculator();
    sidebar = new QWidget(this);
    sidebar->setStyleSheet("background-color: rgb(255, 255, 127);");
    sidebar->resize(100, 100);
    sidebar->show();
}

MainWindow::~MainWindow()
{
    delete mainWindowUi;
    delete content;
}


void MainWindow::generalCalculator(){
    RENDER(GeneralCalculator)
}

void MainWindow::scientificCalculator(){
    RENDER(ScientificCalculator);
}

void MainWindow::buttonPushed(){

}
