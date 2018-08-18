#include <QtWidgets/QTableWidget>
#include <QtWidgets/QHeaderView>
#include "dialog.h"
namespace Dialog {
    Dialog::Dialog(Dialog* dialog) : QDialog(), derived(dialog), changeEventLocked(false){}

    void Dialog::closeEvent(QCloseEvent*){
        this->deleteLater();
    }

    void Dialog::tableInitialize(QTableWidget*& table, const QString& tableName, Table<QString>& dataTable){
        table = this->findChild<QTableWidget*>(tableName);
        dataTable = Table<QString>(table->columnCount());
        table->horizontalHeader()->setStretchLastSection(true);
        table->setCurrentItem(nullptr);
        this->tableMap[table] = &dataTable;
        this->connectTable(table);
    }

    void Dialog::connectTable(QTableWidget* widget){
        connect(widget, &QTableWidget::itemChanged, [this, widget](QTableWidgetItem* item){
            this->contentChangeEvent(item, widget);
        });
    }

    void Dialog::contentChangeEvent(QTableWidgetItem* item, QTableWidget* widget){
        if(!this->isEventEnabled())
            return;
        else{
            derived->contentChanged(item, widget, *this->tableMap[widget]);
        }
    }

    void Dialog::changeWithoutEvent(QTableWidget* widget, int row, int column, QTableWidgetItem* item){
        this->disableChangeEvent();
        widget->setItem(row, column, item);
        this->enableChangeEvent();
    }

    void Dialog::changeWithoutEvent(QTableWidget* widget, int row, int column, const QString& str){
        this->disableChangeEvent();
        widget->item(row, column)->setText(str);
        this->enableChangeEvent();
    }

    void Dialog::changeWithoutEvent(QTableWidgetItem* item, const QString& str){
        this->disableChangeEvent();
        item->setText(str);
        this->enableChangeEvent();
    }

    void Dialog::cleanTable(QTableWidget* table){
        this->disableChangeEvent();
        while(table->rowCount() > 0)
            table->removeRow(0);
        this->enableChangeEvent();
    }

    void Dialog::setRowDisable(QTableWidget* table, int row){
        for(int column = 0; column < table->columnCount(); ++column){
            auto item = table->item(row, column);
            this->disableChangeEvent();
            if(item == nullptr){
                QWidget* widget = table->cellWidget(row, column);
                widget->setEnabled(false);
            }
            else
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            this->enableChangeEvent();
        }
    }

    void Dialog::setItemDisable(QTableWidget* table, int row, int column){
        auto item = table->item(row, column);
        this->disableChangeEvent();
        if(item == nullptr){
            QWidget* widget = table->cellWidget(row, column);
            widget->setEnabled(false);
        }
        else
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        this->enableChangeEvent();
    }

    void Dialog::addItem(QTableWidget* table, const int& row, const int& column, const QString& str){
        QTableWidgetItem *item = new QTableWidgetItem(str);
        this->changeWithoutEvent(table, row, column, item);
        this->tableMap[table]->insert(str, row, column);
    }

    void Dialog::addItem(QTableWidget* table, const int& row, const int& column, QTableWidgetItem* item){
        this->changeWithoutEvent(table, row, column, item);
        this->tableMap[table]->insert(item->text(), row, column);
    }

    void Dialog::enableChangeEvent(){
        this->changeEventLocked = false;
    }

    void Dialog::disableChangeEvent(){
        this->changeEventLocked = true;
    }

    bool Dialog::isEventEnabled(){
        return !this->changeEventLocked;
    }
}
