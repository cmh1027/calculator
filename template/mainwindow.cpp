#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "templates.h"
#include "../config/config.h"

Configuration* config;

MainWindow::MainWindow() :
    currentMenu(nullptr), mainWindowUi(new Ui::MainWindow)
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
    for(auto iter = this->contents.begin(); iter != this->contents.end(); ++iter)
        delete *iter;
}

void MainWindow::loadContents(){
    QWidget* widget;
    Template::Content* content;
    LOAD_CONTENT(Template::GeneralCalculator)
    LOAD_CONTENT(Template::ScientificCalculator)
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
    this->sidebar->setFixedHeight(this->height() + 11);
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
    this->hideMenu();
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    if(!(event->x() < this->sidebar->width() && event->y() < this->sidebar->height()))
        this->hideMenu();
}

void MainWindow::addConstant(const QString &str, const double &num){
    for(auto iter = this->contents.begin(); iter != this->contents.end(); ++iter)
        (*iter)->addConstant(str, num);
}

void MainWindow::removeConstant(const QString &str){
    for(auto iter = this->contents.begin(); iter != this->contents.end(); ++iter)
       (*iter)->removeConstant(str);
}
