#ifndef ADVANCED_H
#define ADVANCED_H
#include <QtWidgets/QTableWidget>
#include "../dialog.h"
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
    class Advanced : public Dialog::Dialog{
        Q_OBJECT

        friend class Dialog::Dialog;

    public:
        Advanced(Template::MathContent*);
        virtual ~Advanced();

    private:
        enum Column{Symbol, Description, Value, Expression, Count};
        Template::MathContent *parent;
        Ui::Advanced *contentUi;
        CMap<QString, Const::ConstObject*>& doubleList;
        QTableWidget *tempTable;
        QTableWidget *permanentTable;
        Table<QString> tempDataTable;
        Table<QString> permanentDataTable;
        void contentChanged(QTableWidgetItem*, QTableWidget*, Table<QString>&) override;
        void addItem(QTableWidget*, const QString&, const Const::ConstObject*, int& index);
        void addItem(QTableWidget*, const QString&, const Const::ConstObject*, int&& index);
        void updateRows();

    private slots:
        void addItem() override;
        void removeItem() override;
        void promoteItem();

    };
}
#endif // ADVANCED_H
