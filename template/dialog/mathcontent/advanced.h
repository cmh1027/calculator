#ifndef ADVANCED_H
#define ADVANCED_H
#include <QtWidgets/QDialog>
#include <QtWidgets/QTableWidget>
#include "../../../module/ctl.h"
#include "../../../module/mathcontent/constant.h"
#include "../../../module/table.h"

namespace Ui {
    class Advanced;
}
namespace Template{
    class MathContent;
}
class QString;

namespace Dialog{
    class Advanced : public QDialog{
        Q_OBJECT

    public:
        Advanced(Template::MathContent*);
        virtual ~Advanced();

    private:
        enum Column{Symbol, Description, Value, Expression, Count};
        Template::MathContent *parent;
        Ui::Advanced *contentUi;
        CMap<QString, Const::ConstObject*>& doubleList;
        void closeEvent(QCloseEvent*);
        void installCells();
        void contentChanged(QTableWidgetItem*, QTableWidget*, Table<QString>&);
        QTableWidget *tempTable;
        QTableWidget *permanentTable;
        void addItem(QTableWidget*, const QString&, const QString&, const QString&, const QString&, int& index);
        void addItem(QTableWidget*, const QString&, const QString&, const QString&, const QString&, int&& index);
        void addItem(const int&, const int&, QTableWidget*, const QString&);
        Table<QString> tempDataTable;
        Table<QString> permanentDataTable;
        void lockedChangeContent(QTableWidget*, int, int, QTableWidgetItem*);
        void lockedChangeContent(QTableWidget*, int, int, const QString&);
        void lockedChangeContent(QTableWidgetItem*, const QString&);
        void updateRows();
        bool lock;

    private slots:
        void addItem();
        void removeItem();
        void promoteItem();

    };
}
#endif // ADVANCED_H
