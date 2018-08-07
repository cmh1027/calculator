#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "module/calculator/constant.h"

#define LOAD_CONFIG(ui, index) \
    content = new ui(this); \
    content->setup(); \
    this->contentWidget->insertWidget(index, content); \

#define LOAD_CONTENT(ui, index) \
    content = new ui(this); \
    content->setup(); \
    this->contentWidget->insertWidget(index, content); \

namespace Ui {
    class MainWindow;
}
class QWidget;
class QStackedWidget;
class QPushButton;
class QLabel;
class QLineEdit;
class QScrollArea;
class QMoustEvent;
class SideMenuLayout;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow();
    virtual ~MainWindow();
    QPushButton *currentMenu;
    void degreeUnitChanged();
    void precisionChanged();
    QStackedWidget *contentWidget;

private:
    Ui::MainWindow *mainWindowUi;
    QScrollArea *sidebar;
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
    void hideAllContentMenu();

public slots:
    void showSideMenu();
    void hideSideMenu();
    void changeContent(const int& menuNum);

};

#endif // MAINWINDOW_H
