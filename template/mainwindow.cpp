#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow() :
    currentMenu(nullptr), config(new Configuration), mainWindowUi(new Ui::MainWindow)
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
    delete config;
    for(auto iter = this->contents.begin(); iter != this->contents.end(); ++iter)
        delete *iter;
}

void MainWindow::loadContents(){
    QWidget* widget;
    Content* content;
    LOAD_CONTENT(GeneralCalculator);
    LOAD_CONTENT(ScientificCalculator);
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
