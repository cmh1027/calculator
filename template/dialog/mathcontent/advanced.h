#ifndef ADVANCED_H
#define ADVANCED_H
#include <QtWidgets/QDialog>
#include <QtWidgets/QTableWidget>
#include "../../../module/ctl.h"
#include "../../../module/calculator/constant.h"

namespace Ui {
    class Advanced;
}
namespace Template{
    class MathContent;
}
class QString;
class MainWindow;

namespace Dialog{
    class Advanced : public QDialog{
        Q_OBJECT

    public:
        Advanced(Template::MathContent*, MainWindow*);
        virtual ~Advanced();

    private:
        MainWindow* mainWindow;
        Template::MathContent *parent;
        Ui::Advanced *contentUi;
        CMap<QString, Const::ConstObject> doubleList;
        void closeEvent(QCloseEvent*);
        QTableWidget *tempTable;
        QTableWidget *permanentTable;
        void addTemp(const QString&, const QString&, const QString&, int& index);
        void addPermanent(const QString&, const QString&, const QString&, int& index);

    private slots:
        void addItem();
        void removeItem();

    };
}
#endif // ADVANCED_H
