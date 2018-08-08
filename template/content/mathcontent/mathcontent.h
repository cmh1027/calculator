#ifndef MATHCONTENT_H
#define MATHCONTENT_H
#include <QVector>
#include "../content.h"
#include "../../../module/ctl.h"
#include "../../../module/calculator/constant.h"
#include "calculator/menu/constmenulayout.h"
#include "calculator/menu/funcmenulayout.h"

class MainWindow;
class QWidget;
class QString;
class MenuLayout;

namespace Template{
    class MathContent : public Content{
        Q_OBJECT

    public:
        MathContent(MainWindow*);
        virtual ~MathContent();
        void addConstant(const QString &str, const Const::ConstObject& num);
        void removeConstant(const QString &str);
        const CMap<QString, Const::ConstObject>* getDoubleList();
        void hideAllMenus();

    protected:
        CMap<QString, Const::ConstObject> doubleList; // constant & repeating decimal symbolic calculation
        QVector<MenuLayout*> menus;
        virtual void installMenu() = 0;

    private:
        QWidget* contentWidget;
        void mousePressEvent(QMouseEvent*);
    };
}
#endif // MATHCONTENT_H
