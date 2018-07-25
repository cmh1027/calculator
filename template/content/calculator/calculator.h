#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <QMainWindow>
#include <QtWidgets/QLabel>
#include <QString>
#include <iostream>
#include "../content.h"
#include "../../../module/calculator/operator.h"
#include "../../../module/calculator/constant.h"

using namespace Const;

class Calculator : public Content
{
    Q_OBJECT

public:
    Calculator(QMainWindow *window);
    virtual ~Calculator();

private:
    QMainWindow *MainWindow;
    QLabel *interLabel;
    QLabel *resultLabel;

protected:
    bool calculated;
    bool specialStart;
    void bindLabels();
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
    bool isBracketUnclosed(const QString &expr) const;
    bool endsWithBracket() const;
    void closeAllBracket();
    bool isLastOpArithmetic() const;
    void replaceLastOp(const QString &str);
    void addNumber(const QString &str);
    void constant(const double &constant);
};
#endif // CALCULATOR_H
