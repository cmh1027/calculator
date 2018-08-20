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
        template<typename C, typename List>
        void installCells(C ptr, List list, QTableWidget* permanentTable){
            int permanent = 0;
            this->disableChangeEvent();
            this->cleanTable(permanentTable);
            this->tableMap[permanentTable]->rowClear();
            for(auto it = list.begin(); it != list.end(); it++){
                ptr->addItem(permanentTable, it.key(), (*it), permanent);
                if((*it)->isDefault())
                    this->setRowDisable(permanentTable, permanent-1);
            }
            this->enableChangeEvent();
        }
        template<typename C, typename List>
        void installCells(C ptr, List list, QTableWidget* permanentTable, QTableWidget* tempTable){
            int temp = 0;
            int permanent = 0;
            this->disableChangeEvent();
            this->cleanTable(tempTable);
            this->cleanTable(permanentTable);
            this->tableMap[tempTable]->rowClear();
            this->tableMap[permanentTable]->rowClear();
            for(auto it = list.begin(); it != list.end(); it++){
                if((*it)->isTemp()){
                    ptr->addItem(tempTable, it.key(), (*it), temp);
                }
                else{
                    ptr->addItem(permanentTable, it.key(), (*it), permanent);
                    if((*it)->isDefault())
                        this->setRowDisable(permanentTable, permanent-1);
                }
            }
            this->enableChangeEvent();
        }
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
