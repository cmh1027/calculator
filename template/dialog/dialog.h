#ifndef DIALOG_H
#define DIALOG_H
#include <QMap>
#include <QtWidgets/QDialog>
#include "../../module/table.h"

class QTableWidget;
class QTableWidgetItem;

namespace Dialog{
    class Dialog : public QDialog{
        Q_OBJECT

    public:
        Dialog(Dialog*);
        virtual ~Dialog() = default;

    protected:
        void tableInitialize(QTableWidget*&, const QString&, Table<QString>&);
        void connectTable(QTableWidget*);
        virtual void installCells() = 0;
        void changeWithoutEvent(QTableWidget*, int, int, QTableWidgetItem*);
        void changeWithoutEvent(QTableWidget*, int, int, const QString&);
        void changeWithoutEvent(QTableWidgetItem*, const QString&);
        void cleanTable(QTableWidget*);
        void setRowDisable(QTableWidget*, int);
        void setItemDisable(QTableWidget*, int, int);
        void addItem(QTableWidget*, const int&, const int&, const QString&);
        void addItem(QTableWidget*, const int&, const int&, QTableWidgetItem*);
        virtual void contentChanged(QTableWidgetItem*, QTableWidget*, Table<QString>&) = 0;
        QMap<QTableWidget*, Table<QString>*> tableMap;
        void enableChangeEvent();
        void disableChangeEvent();
        bool isEventEnabled();


    private:
        Dialog* derived;
        bool changeEventLocked;
        void closeEvent(QCloseEvent*);

    protected slots:
        virtual void addItem() = 0;
        virtual void removeItem() = 0;

    private slots:
        void contentChangeEvent(QTableWidgetItem*, QTableWidget*);
    };
}
#endif // DIALOG_H
