#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QPushButton>
#include <QMouseEvent>
#include <QVector>

class Content;
class Configuration;

#define LOAD_CONTENT(ui) \
    widget = new QWidget; \
    content = new ui(this, widget); \
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
    Configuration *config;

private:
    Ui::MainWindow *mainWindowUi;
    QStackedWidget *contentWidget;
    QVector<Content*> contents;
    QWidget *sidebar;
    void loadContents();
    void installSidebar();
    void generalCalculator();
    void scientificCalculator();
    void setTitle(const QString &str);
    void mousePressEvent(QMouseEvent *event);

public slots:
    void showMenu();
    void hideMenu();
    void changeContent(const int& menuNum);
};

#endif // MAINWINDOW_H
