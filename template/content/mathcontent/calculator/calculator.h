#ifndef CALCULATOR_H
#define CALCULATOR_H
#include "../mathcontent.h"

class QPushButton;
class QLabel;
class QLineEdit;
class QString;
class QScrollArea;
namespace Ui {
    class Calculator;
}

class MainWindow;

namespace Template{
    class Calculator : public Template::MathContent
    {
        Q_OBJECT

    public:
        Calculator(MainWindow*);
        virtual ~Calculator();
        void precisionChanged();
        void enableLineEdit();
        void disableLineEdit();
        void constant(const QString &constant);

    private:
        Ui::Calculator *contentUi;
        QWidget *contentWidget;
        QLabel *interLabel;
        QScrollArea *interScrollArea;
        QLineEdit *interLineEdit;
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
        bool startWithBracket(const QString &expr) const;
        bool endWithBracket() const;
        bool endWithBracket(const QString &expr) const;
        void closeAllBracket();
        bool isLastOpArithmetic() const;
        bool isLastOpOperator() const;
        void replaceLastOp(const QString &str);
        void addNumber(const QString &str);
        void changeButton(const QString &targetName, const QString &buttonName, const QString &icon);
        void clearDoubleList();
        void clearDoubleListEqual();
        bool isModifying;
        void installMenu() override;

    public slots:
        virtual void buttonPushed() = 0;
    };
}
#endif // CALCULATOR_H
