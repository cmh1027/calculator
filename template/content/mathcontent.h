#ifndef MATHCONTENT_H
#define MATHCONTENT_H
#include <QtWidgets/QWidget>
#include <QString>
#include "content.h"
#include "../../module/ctl.h"
#include "../../module/calculator/constant.h"

class MainWindow;

namespace Template{
    class MathContent : public Content{
        Q_OBJECT

    public:
        MathContent(MainWindow*);
        virtual ~MathContent();
        void addConstant(const QString &str, const Const::ConstObject& num);
        void removeConstant(const QString &str);

    protected:
        CMap<QString, Const::ConstObject> doubleList; // constant & repeating decimal symbolic calculation

    private:
        QWidget* contentWidget;

    public slots:
        virtual void buttonPushed() = 0;
    };
}
#endif // MATHCONTENT_H
