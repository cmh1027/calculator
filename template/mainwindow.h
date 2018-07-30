#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QPushButton>
#include <QMouseEvent>
#include <QVector>

namespace Template{
    class Content;
    class Configuration;
}

#define LOAD_CONFIG \
    Template::Configuration* configTemplate; \
    widget = new QWidget; \
    configTemplate = new Template::Configuration(this, widget); \
    configTemplate->setup(); \
    this->contentWidget->addWidget(widget); \
    this->configTemplate = configTemplate;

#define LOAD_CONTENT(ui) \
    widget = new QWidget; \
    content = new ui(widget); \
    content->setup(); \
    this->contentWidget->addWidget(widget); \
    this->contents.append(content);

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
    QVector<Template::Content*> contents;
    QWidget *sidebar;
    Template::Configuration *configTemplate;
    void loadContents();
    void installSidebar();
    void generalCalculator();
    void scientificCalculator();
    void setTitle(const QString &str);
    void mousePressEvent(QMouseEvent *event);
    void addConstant(const QString &str, const double &num);
    void removeConstant(const QString &str);

public slots:
    void showMenu();
    void hideMenu();
    void changeContent(const int& menuNum);

};

#endif // MAINWINDOW_H
