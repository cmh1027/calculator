#ifndef GENERAL_H
#define GENERAL_H
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtCore/QRegExp>
#include <QString>
#include <QMap>
#include <utility>
#include <iostream>
#include "../calculator.h"

class MainWindow;

namespace Ui {
    class GeneralCalculator;
}

class GeneralCalculator : public Calculator
{
    Q_OBJECT

public:
    GeneralCalculator(MainWindow*, QWidget*);
    virtual ~GeneralCalculator();
    void setup() override;

private:
    Ui::GeneralCalculator *contentUi;
    QWidget *contentWidget;

protected:
    void calculate();
    void calculate(const QString &op);
    QString calculateExpression(QString expr);
    void arithmetic(const QString &op);
    void unarySpecial(const QString &format);
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
    void leftBracket();
    void rightBracket();
    QMap<QString, void(GeneralCalculator::*)()> Operators;

public slots:
    void buttonPushed() override;
};

#endif // GENERAL_H
