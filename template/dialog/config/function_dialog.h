#ifndef FUNCTION_DIALOG
#define FUNCTION_DIALOG
#include "../dialog.h"
#include "../../../module/ctl.h"
#include "../../../module/mathcontent/operator.h"
#include "../../../module/table.h"

namespace Ui {
    class Function;
}

class QString;
class QTableWidget;
class QComboBox;
namespace Dialog{
    class Function : public Dialog::Dialog{
        Q_OBJECT

        friend class Dialog::Dialog;

    public:
        Function();
        virtual ~Function();

    private:
        enum Column{Symbol, Description, Arity, Blank, Expression, Count};
        Ui::Function *contentUi;
        CMap<QString, Operation::OperationObject*>& funcList;
        QTableWidget *permanentTable;
        Table<QString> permanentDataTable;
        void contentChanged(QTableWidgetItem*, QTableWidget*, Table<QString>&) override;
        void addItem(QTableWidget*, const QString&, Operation::OperationObject*, int& index);
        void addItem(QTableWidget*, const QString&, Operation::OperationObject*, int&& index);
        void setArityTableItem(QTableWidget*, int, int, Operation::OperationObject*);
        void setExprTableItem(QTableWidget*, int, int, Operation::OperationObject*);
        void unknown(const QString&, Operation::Arity);

    private slots:
        void addItem() override;
        void removeItem() override;

    };
}
#endif
