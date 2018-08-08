#ifndef MATHCONTENT_H
#define MATHCONTENT_H
#include <QVector>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include "../content.h"
#include "../../../module/ctl.h"
#include "../../../module/calculator/constant.h"

class MainWindow;
class QWidget;
class QString;
class MathMenuLayout;


namespace Template{
    class MathContent : public Content{
        Q_OBJECT

    public:
        MathContent(MainWindow*);
        virtual ~MathContent();
        void addConstant(const QString &str, const Const::ConstObject& num);
        void removeConstant(const QString &str);
        const CMap<QString, Const::ConstObject>& getDoubleList();
        void hideAllMenus();
        void moveAllMenus();

    protected:
        CMap<QString, Const::ConstObject> doubleList; // constant & repeating decimal symbolic calculation
        QVector<MathMenuLayout*> menus;
        virtual void installMenu() = 0;
        template <class T, class Self>
        void install(const QString& scrollAreaName, QPushButton* standard){
            QScrollArea* scrollArea;
            MathMenuLayout* menuLayout;
            scrollArea = this->findChild<QScrollArea*>(scrollAreaName);
            menuLayout = new T(this->mainWindow, static_cast<Self*>(this), scrollArea, standard);
            this->menus.push_back(menuLayout);
            connect(standard, &QPushButton::clicked, this, [menuLayout](){
                static_cast<T*>(menuLayout)->click();
            });
        }


    private:
        QWidget* contentWidget;
        void mousePressEvent(QMouseEvent*);
    };
}
#endif // MATHCONTENT_H
