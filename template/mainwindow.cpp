#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow() :
    currentMenu(nullptr), mainWindowUi(new Ui::MainWindow)
{
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
    Content* content;
    LOAD_CONTENT(GeneralCalculator);
    LOAD_CONTENT(ScientificCalculator);
}


void MainWindow::installSidebar(){
    this->sidebar = this->findChild<QWidget*>("menubarWidget");
    this->sidebar->setParent(this);
    this->sidebar->setFixedHeight(this->height() + 11);
    connect(this->sidebar->findChild<QToolButton*>("menuCloseButton"), &QToolButton::clicked, this, this->hideMenu);
    MenuLayout *sidebarLayout = new MenuLayout(this);
    this->sidebar->findChild<QWidget*>("scrollAreaWidgetContents")->setLayout(sidebarLayout);
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
    this->currentMenu->setStyleSheet("background-color: transparent;");
    this->currentMenu = senderButton;
    this->currentMenu->setStyleSheet("background-color: rgb(119, 162, 255);");
    this->contentWidget->setCurrentIndex(menuNum);
}
