#ifndef CONSTANT_DIALOG
#define CONSTANT_DIALOG
#include <QtWidgets/QTableWidget>
#include "../dialog.h"
#include "../../../module/ctl.h"
#include "../../../module/mathcontent/constant.h"
#include "../../../module/table.h"

namespace Ui {
    class Constant;
}
class QString;

namespace Dialog{
    class Constant : public Dialog::Dialog{
        Q_OBJECT

        friend class Dialog::Dialog;

    public:
        Constant();
        virtual ~Constant();

    private:
        enum Column{Symbol, Description, Value, Expression, Count};
        Ui::Constant *contentUi;
        CMap<QString, Const::ConstObject*>& doubleList;
        QTableWidget *permanentTable;
        Table<QString> permanentDataTable;
        void installCells() override;
        void contentChanged(QTableWidgetItem*, QTableWidget*, Table<QString>&) override;
        void addItem(QTableWidget*, const QString&, const Const::ConstObject*, int& index);
        void addItem(QTableWidget*, const QString&, const Const::ConstObject*, int&& index);
        void updateRows();

    private slots:
        void addItem() override;
        void removeItem() override;

    };
}
#endif
