#include <QtWidgets/QWidget>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QScrollArea>
#include <QMouseEvent>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "templates.h"
#include "../config/config.h"

Configuration* config;

MainWindow::MainWindow() :
    currentMenu(nullptr), mainWindowUi(new Ui::MainWindow), currentIndex(0)
{
    config = new Configuration(this);
    mainWindowUi->setupUi(this);
    this->installSidebar();
    this->contentWidget = this->findChild<QStackedWidget*>("contentWidget");
    this->loadContents();
    connect(this->findChild<QToolButton*>("menuButton"), &QToolButton::clicked, this, &this->showSideMenu);
}

MainWindow::~MainWindow()
{
    delete mainWindowUi;
    for(int i = 0; i < this->contentWidget->count(); i++)
        delete this->contentWidget->widget(i);
}

void MainWindow::loadContents(){
    LOAD_CONTENT(Template::GeneralCalculator, 0);
    LOAD_CONTENT(Template::ScientificCalculator, 1);
    LOAD_CONTENT(Template::Table, 2);
    LOAD_CONTENT(Template::Graph, 3);
    LOAD_CONTENT(Template::Matrix, 4);
    LOAD_CONFIG(Template::Configuration, 5);
}

void MainWindow::setTitle(const QString &str){
    this->findChild<QLabel*>("titleLabel")->setText(str);
}

void MainWindow::installSidebar(){
    this->sidebar = this->findChild<QScrollArea*>("menubarScrollArea");
    SideMenuLayout sidebarLayout(this, this->sidebar);
    sidebarLayout.applyLayout();
}

void MainWindow::showSideMenu(){
    this->hideAllContentMenu();
    this->sidebar->show();
}

void MainWindow::hideSideMenu(){
    this->sidebar->hide();
}

void MainWindow::changeContent(const int& menuNum){
    auto senderButton = static_cast<QPushButton*>(sender());
    this->setTitle(senderButton->text());
    this->currentMenu->setStyleSheet("QPushButton{text-align: left;padding-left:50px;}"
                                     "QPushButton:hover{background-color: rgb(207, 207, 207);}");
    this->currentMenu = senderButton;
    this->currentMenu->setStyleSheet("QPushButton{background-color: rgb(119, 162, 255);"
                                     "text-align: left;padding-left:50px;}"
                                     "QPushButton:hover{background-color: rgb(144, 144, 255);}");
    this->contentWidget->setCurrentIndex(menuNum);
    this->currentIndex = menuNum;
    this->hideSideMenu();
}


void MainWindow::addConstant(const QString &str, const Const::ConstObject& num){
    Template::MathContent* ptr;
    for(int i = 0; i < this->contentWidget->count(); i++){
        if((ptr = dynamic_cast<Template::MathContent*>(this->contentWidget->widget(i))) != nullptr)
            ptr->addConstant(str, num);
    }
}

void MainWindow::removeConstant(const QString &str){
    Template::MathContent* ptr;
    for(int i = 0; i < this->contentWidget->count(); i++){
        if((ptr = dynamic_cast<Template::MathContent*>(this->contentWidget->widget(i))) != nullptr)
            ptr->removeConstant(str);
    }
}

void MainWindow::degreeUnitChanged(){
    Template::GeneralCalculator* ptr;
    for(int i = 0; i < this->contentWidget->count(); i++){
        if((ptr = dynamic_cast<Template::GeneralCalculator*>(this->contentWidget->widget(i))) != nullptr){
            ptr->calculateAgain();
        }
    }
}

void MainWindow::precisionChanged(){
    Template::Calculator* ptr;
    for(int i = 0; i < this->contentWidget->count(); i++){
        if((ptr = dynamic_cast<Template::Calculator*>(this->contentWidget->widget(i))) != nullptr){
            ptr->precisionChanged();
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent*){
    if(!this->sidebar->underMouse()){
        this->hideSideMenu();
    }
    if(!this->contentWidget->underMouse()){
        this->hideAllContentMenu();
    }
}

void MainWindow::resizeEvent(QResizeEvent*){
    this->sidebar->setFixedHeight(this->height() + 11);
}

void MainWindow::hideAllContentMenu(){
    Template::MathContent* ptr;
    for(int i = 0; i < this->contentWidget->count(); i++){
        if((ptr = dynamic_cast<Template::MathContent*>(this->contentWidget->widget(i))) != nullptr)
            ptr->hideAllMenus();
    }
}
