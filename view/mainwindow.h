#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLabel>
#include <QtCore/QRegExp>
#include <QString>
#include <QMap>
#include <utility>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QLabel *interLabel;
    QLabel *resultLabel;
    bool calculated;
    const QMap<QString, void(MainWindow::*)()> Operators;
    void setResult(const QString &str);
    void addResult(const QString &str);
    QString getResult() const;
    void setInter(const QString &str);
    void addInter(const QString &str);
    QString getInter() const;
    QString lastOp() const;
    bool isLastOpArithmetic() const;
    void replaceLastOp(const QString &str);
    void addNumber(const QString &str);
    void calculate();
    void arithmetic(const QString &op);
    void plus();
    void minus();
    void multiply();
    void divide();
public slots:
    void buttonPushed();

};

#endif // MAINWINDOW_H
