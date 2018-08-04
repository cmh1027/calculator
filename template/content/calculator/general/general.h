#ifndef GENERAL_H
#define GENERAL_H
#include <QString>
#include "../../../../module/ctl.h"
#include "../calculator.h"

namespace Ui {
    class GeneralCalculator;
}

namespace Template{
    class GeneralCalculator : public Template::Calculator
    {
        Q_OBJECT

    public:
        GeneralCalculator();
        virtual ~GeneralCalculator();
        void setup() override;
        void calculateAgain();
        void disableLineEdit();

    private:
        Ui::GeneralCalculator *contentUi;
        QWidget *contentWidget;
        void buttonConnect() override;

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
        CMap<QString, void(GeneralCalculator::*)()> Operators;
        void mousePressEvent(QMouseEvent*);

    public slots:
        void buttonPushed() override;
    };
}

#endif // GENERAL_H
