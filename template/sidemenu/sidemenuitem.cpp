#include <QString>
#include <QtWidgets/QWidget>
#include "sidemenuitem.h"
#include "../mainwindow.h"
SideMenuItem::SideMenuItem(MainWindow *window, QWidget *parent, const QString &text, const int &num) :
    MenuItem(parent, text), mainWindow(window){
    int height = parent->findChild<QWidget*>("menuTitleWidget")->height();
    this->setFixedHeight(height);
    this->move(0, height*(num+1));
    this->font(12, true);
    connect(this, &SideMenuItem::clicked, window, [window, num](){
        window->changeContent(num);
    });
    this->setStyleSheet("QPushButton{text-align: left;padding-left:50px;}"
                        "QPushButton:hover{background-color: rgb(207, 207, 207);}");

}

SideMenuItem* SideMenuItem::selected(){
    this->setStyleSheet("QPushButton{background-color: rgb(119, 162, 255);"
                        "text-align: left;padding-left:50px;}"
                        "QPushButton:hover{background-color: rgb(144, 144, 255);}");
    this->mainWindow->currentMenu = this;
    return this;
}
