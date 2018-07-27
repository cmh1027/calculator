#include "menuItem.h"

MenuItem::MenuItem(QMainWindow *window, QWidget *parent, const QString &text, const int &num) :
    QPushButton(), mainWindow(window){
    this->setText(text);
    int height = parent->findChild<QWidget*>("menuTitleWidget")->height();
    this->setFixedHeight(height);
    this->setFixedWidth(parent->width());
    this->move(0, (num+1)*height);
    QFont font;
    font.setFamily(QString::fromUtf8("\353\247\221\354\235\200 \352\263\240\353\224\225"));
    font.setPointSize(12);
    font.setBold(true);
    font.setWeight(75);
    this->setFont(font);
    connect(this, &MenuItem::clicked, window, [window, num](){
        static_cast<MainWindow*>(window)->changeContent(num);
    });
}

MenuItem* MenuItem::selected(){
    this->setStyleSheet("QPushButton{background-color: rgb(119, 162, 255);"
                        "text-align: left;padding-left:50px;}"
                        "QPushButton:hover{background-color: rgb(144, 144, 255);}");
    static_cast<MainWindow*>(this->mainWindow)->currentMenu = this;
    return this;
}
MenuItem* MenuItem::unselected(){
    this->setStyleSheet("QPushButton{text-align: left;padding-left:50px;}"
                        "QPushButton:hover{background-color: rgb(207, 207, 207);}");
    return this;
}
