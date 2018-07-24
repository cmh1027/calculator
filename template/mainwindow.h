#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtCore/QRegExp>
#include <QString>
#include <QMap>
#include <utility>
#include "../module/calculator/operator.h"

namespace Ui {
    class MainWindow;
    class Form;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *mainWindowUi;
    Ui::Form *contentUi;
    QLabel *interLabel;
    QLabel *resultLabel;
    bool calculated;
    bool specialStart;
    const QMap<QString, void(MainWindow::*)()> Operators;
    void setResult(const QString &str);
    void appendResult(const QString &str);
    void prependResult(const QString &str);
    void chopResult(const int &num);
    void removeResult(const int &num);
    void removeResult(const int &pos, const int &num);
    QString getResult(const bool &chopDot = true);
    void setInter(const QString &str);
    void appendInter(const QString &str, const bool &autoSpace = true);
    void prependInter(const QString &str, const bool &autoSpace = true);
    void chopInter(const int &num);
    void removeInter(const int &num);
    void removeInter(const int &pos, const int &num);
    QString chopInterOp(const int &num);
    QString removeInterOp(const int &num);
    QString getInter() const;
    QString lastOp() const;
    bool isBracketUnclosed() const;
    bool endsWithBracket() const;
    void closeAllBracket();
    bool isLastOpArithmetic() const;
    void replaceLastOp(const QString &str);
    void addNumber(const QString &str);
    void calculate();
    void calculate(const QString &op);
    void arithmetic(const QString &op);
    void unarySpecial(const QString &format);
    void binarySpecial(const QString &format);
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
    void inv();
    void root();
    void pow();
    void sin();
    void cos();
    void tan();
    void asin();
    void acos();
    void atan();
    void sinh();
    void cosh();
    void tanh();
    void log();
    void mod();
    void fac();
public slots:
    void buttonPushed();

};

#endif // MAINWINDOW_H
