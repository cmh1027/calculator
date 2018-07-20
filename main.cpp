#include "view/mainwindow.h"
#include <QApplication>
#include <QtWidgets/QMainWindow>
#include <iostream>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
