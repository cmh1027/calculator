#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QMouseEvent>

namespace Template{
    class Content;
    class Configuration;
}

#define LOAD_CONFIG() \
    Template::Configuration* configTemplate; \
    configTemplate = new Template::Configuration(this); \
    configTemplate->setup(); \
    this->contentWidget->addWidget(configTemplate); \
    this->configTemplate = configTemplate; \

#define LOAD_CONTENT(ui) \
    content = new ui(); \
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
    Template::Configuration *configTemplate;
    void loadContents();
    void installSidebar();
    void generalCalculator();
    void scientificCalculator();
    void setTitle(const QString &str);
    void addConstant(const QString &str, const double &num);
    void removeConstant(const QString &str);
    void mousePressEvent(QMouseEvent*);
    int currentIndex;

public slots:
    void showMenu();
    void hideMenu();
    void changeContent(const int& menuNum);

};

#endif // MAINWINDOW_H
