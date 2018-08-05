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
    connect(this->findChild<QToolButton*>("menuButton"), &QToolButton::clicked, this, &this->showMenu);
}

MainWindow::~MainWindow()
{
    delete mainWindowUi;
    for(int i = 0; i < this->contentWidget->count(); i++)
        delete this->contentWidget->widget(i);
}

void MainWindow::loadContents(){
    Template::Content* content;
    LOAD_CONTENT(Template::GeneralCalculator)
    LOAD_CONTENT(Template::ScientificCalculator)
    LOAD_CONFIG(Template::Configuration)
}

void MainWindow::setTitle(const QString &str){
    this->findChild<QLabel*>("titleLabel")->setText(str);
}

void MainWindow::installSidebar(){
    this->sidebar = this->findChild<QWidget*>("menubarWidget");
    this->sidebar->setParent(this);
    this->sidebar->setFixedHeight(this->height() + 11);
    connect(this->sidebar->findChild<QToolButton*>("menuCloseButton"), &QToolButton::clicked, this, &this->hideMenu);
    MenuLayout *sidebarLayout = new MenuLayout(this, this->sidebar->findChild<QWidget*>("scrollAreaWidgetContents"));
    sidebarLayout->applyLayout();
    this->sidebar->hide();
}

void MainWindow::showMenu(){
    this->sidebar->show();
}

void MainWindow::hideMenu(){
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
    this->hideMenu();
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
        this->hideMenu();
    }
}

void MainWindow::resizeEvent(QResizeEvent*){
    this->sidebar->setFixedHeight(this->height() + 11);
}
