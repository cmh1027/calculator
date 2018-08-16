#ifndef CONSTANT_DIALOG
#define CONSTANT_DIALOG
#include <QtWidgets/QDialog>
#include <QtWidgets/QTableWidget>
#include "../../../module/ctl.h"
#include "../../../module/mathcontent/constant.h"
#include "../../../module/table.h"

namespace Ui {
    class Constant;
}
class QString;

namespace Dialog{
    class Constant : public QDialog{
        Q_OBJECT

    public:
        Constant();
        virtual ~Constant();

    private:
        enum Column{Symbol, Description, Value, Expression, Count};
        Ui::Constant *contentUi;
        CMap<QString, Const::ConstObject*>& doubleList;
        void closeEvent(QCloseEvent*);
        void installCells();
        void contentChanged(QTableWidgetItem*, QTableWidget*, Table<QString>&);
        QTableWidget *permanentTable;
        void addItem(QTableWidget*, const QString&, const QString&, const QString&, const QString&, int& index);
        void addItem(QTableWidget*, const QString&, const QString&, const QString&, const QString&, int&& index);
        void addItem(const int&, const int&, QTableWidget*, const QString&);
        Table<QString> permanentDataTable;
        void lockedChangeContent(QTableWidget*, int, int, QTableWidgetItem*);
        void lockedChangeContent(QTableWidget*, int, int, const QString&);
        void lockedChangeContent(QTableWidgetItem*, const QString&);
        void updateRows();
        bool lock;

    private slots:
        void addItem();
        void removeItem();

    };
}
#endif
