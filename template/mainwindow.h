#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "content/content.h"
#include "content/calculator/general.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow();
    ~MainWindow();

private:
    Ui::MainWindow *mainWindowUi;
    Content *content;
    void generalCalculator();

public slots:
    void buttonPushed();
};

#endif // MAINWINDOW_H
