#include "menuItem.h"

MenuItem::MenuItem(QMainWindow *mainWindow, const QString &text, const int &num){
    this->setText(text);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setMaximumHeight(40);
    connect(this, &MenuItem::clicked, mainWindow, [mainWindow, num](){
        static_cast<MainWindow*>(mainWindow)->changeContent(num);
    });
}
