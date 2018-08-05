#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QMouseEvent>
#include "module/calculator/constant.h"

#define LOAD_CONFIG(ui) \
    content = new ui(this); \
    content->setup(); \
    this->contentWidget->addWidget(content); \

#define LOAD_CONTENT(ui) \
    content = new ui(this); \
    content->setup(); \
    this->contentWidget->addWidget(content); \

namespace Ui {
    class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow();
    ~MainWindow();
    QPushButton *currentMenu;
    void degreeUnitChanged();
    void precisionChanged();

private:
    Ui::MainWindow *mainWindowUi;
    QStackedWidget *contentWidget;
    QWidget *sidebar;
    void loadContents();
    void installSidebar();
    void generalCalculator();
    void scientificCalculator();
    void setTitle(const QString &str);
    void addConstant(const QString &str, const Const::ConstObject& num);
    void removeConstant(const QString &str);
    void mousePressEvent(QMouseEvent*);
    void resizeEvent(QResizeEvent*);
    int currentIndex;

public slots:
    void showMenu();
    void hideMenu();
    void changeContent(const int& menuNum);

};

#endif // MAINWINDOW_H
