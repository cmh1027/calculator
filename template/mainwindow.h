#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "module/mathcontent/constant.h"


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
    void addConstant(const QString &str, Const::ConstObject* num);
    void removeConstant(const QString &str);
    void refreshAllContents();
    void degreeUnitChanged();
    void precisionChanged();
    QStackedWidget *contentWidget;

private:
    Ui::MainWindow *mainWindowUi;
    QScrollArea *sidebar;
    SideMenuLayout *sideMenuLayout;
    void loadContents();
    void installSidebar();
    void generalCalculator();
    void scientificCalculator();
    void setTitle(const QString &str);
    void mousePressEvent(QMouseEvent*);
    void resizeEvent(QResizeEvent*);
    int currentIndex;
    void hideAllContentMenu();
    template <class T>
    void loadContent(int index);

public slots:
    void showSideMenu();
    void hideSideMenu();
    void changeContent(const int& menuNum);

};

#endif // MAINWINDOW_H
