#ifndef DIALOG_H
#define DIALOG_H
#include <QtWidgets/QDialog>
#include <QtWidgets/QTableWidget>
#include "../../module/table.h"

#define INIT_TABLE(table, tableName, dataTable) \
    table = this->findChild<QTableWidget*>(tableName); \
    dataTable = Table<QString>(table->columnCount()); \
    table->horizontalHeader()->setStretchLastSection(true); \
    table->setCurrentItem(nullptr); \
    this->tableMap[table] = &dataTable;

namespace Dialog{
    class Dialog : public QDialog{
        Q_OBJECT

    public:
        Dialog();
        virtual ~Dialog() = default;

    protected:
        bool lock;
        void lockedChangeContent(QTableWidget*, int, int, QTableWidgetItem*);
        void lockedChangeContent(QTableWidget*, int, int, const QString&);
        void lockedChangeContent(QTableWidgetItem*, const QString&);
        void cleanTable(QTableWidget*);
        void setRowDisable(QTableWidget*, int);
        void setItemDisable(QTableWidget*, int, int);
        void addItem(QTableWidget*, const int&, const int&, const QString&);
        void addItem(QTableWidget*, const int&, const int&, QTableWidgetItem*);
        virtual void contentChanged(QTableWidgetItem*, QTableWidget*, Table<QString>&) = 0;
        virtual void installCells() = 0;
        QMap<QTableWidget*, Table<QString>*> tableMap;

    private:
        void closeEvent(QCloseEvent*);

    protected slots:
        virtual void addItem() = 0;
        virtual void removeItem() = 0;

    };
}
#endif // DIALOG_H
