#include "template/mainwindow.h"
#include <QApplication>
#include <QtWidgets/QMainWindow>
#include <iostream>
#include <QString>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
