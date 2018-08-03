#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QString>
#include "../content.h"

namespace Ui {
    class Calculator;
}
namespace Template{
    class Calculator : public Template::Content
    {
        Q_OBJECT

    public:
        Calculator(QWidget*);
        virtual ~Calculator();
        void precisionChanged();

    private:
        Ui::Calculator *contentUi;
        QWidget *contentWidget;
        QLabel *interLabel;
        QLabel *resultLabel;

    protected:
        bool calculated;
        bool specialStart;
        QString inter;
        QString result;
        void setResult(const QString &str);
        QString getResult(const bool &chopDot = true);
        void appendResult(const QString &str);
        void prependResult(const QString &str);
        void chopResult(const int &num);
        void removeResult(const int &num);
        void removeResult(const int &pos, const int &num);
        void setInter(const QString &str);
        QString getInter() const;
        void appendInter(const QString &str, const bool &autoSpace = true);
        void prependInter(const QString &str, const bool &autoSpace = true);
        void chopInter(const int &num);
        void removeInter(const int &num);
        void removeInter(const int &pos, const int &num);
        QString chopInterOp(const int &num);
        QString lastOp() const;
        QString lastOp(const QString& str) const;
        bool isBracketUnclosed() const;
        bool isBracketUnclosed(const QString &expr) const;
        bool endsWithBracket() const;
        bool endsWithBracket(const QString &expr) const;
        bool isUnarySpecial(const QString &expr) const;
        void closeAllBracket();
        bool isLastOpArithmetic() const;
        bool isLastOpOperator() const;
        void replaceLastOp(const QString &str);
        void addNumber(const QString &str);
        void constant(const QString &constant);
        void changeButton(const QString &targetName, const QString &buttonName, const QString &icon);
        void clearDoubleList();
    };
}
#endif // CALCULATOR_H
