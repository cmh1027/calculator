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
    void appendResult(const QString &str);
    void prependResult(const QString &str);
    void chopResult(const int &num);
    void removeResult(const int &num);
    void removeResult(const int &pos, const int &num);
    QString getResult(const bool &chopDot = true);
    void setInter(const QString &str);
    void appendInter(const QString &str);
    void prependInter(const QString &str);
    void chopInter(const int &num);
    void removeInter(const int &num);
    void removeInter(const int &pos, const int &num);
    QString chopInterOp(const int &num);
    QString removeInterOp(const int &num);
    QString getInter() const;
    QString lastOp() const;
    bool isLastOpArithmetic() const;
    void replaceLastOp(const QString &str);
    void addNumber(const QString &str);
    void calculate();
    void calculate(const QString &op);
    void arithmetic(const QString &op);
    void plus();
    void minus();
    void multiply();
    void divide();
    void equal();
    void erase();
    void dot();
    void negate();
    void ce();
    void c();
    void percent();
    void sqrt();
    void sqr();
    void inverse();
    void root();
    void pow();
public slots:
    void buttonPushed();

};

#endif // MAINWINDOW_H
