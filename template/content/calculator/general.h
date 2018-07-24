#ifndef GENERAL_H
#define GENERAL_H
#include <QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtCore/QRegExp>
#include <QString>
#include <QMap>
#include <utility>
#include <iostream>
#include "../content.h"
#include "../../../module/calculator/operator.h"
#include "../../../module/calculator/calculator.h"

namespace Ui {
    class Form;
}

class GeneralCalculator : public Content
{
    Q_OBJECT

public:
    GeneralCalculator(QMainWindow*);
    virtual ~GeneralCalculator();

private:
    Ui::Form *contentUi;

protected:
    QMainWindow* MainWindow;
    QLabel *interLabel;
    QLabel *resultLabel;
    bool calculated;
    bool specialStart;
    const QMap<QString, void(GeneralCalculator::*)()> Operators;
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
    void buttonPushed() override;
};

#endif // GENERAL_H
