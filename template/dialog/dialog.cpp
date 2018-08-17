#include "dialog.h"
namespace Dialog {
    Dialog::Dialog() : QDialog(), lock(false){}
    void Dialog::lockedChangeContent(QTableWidget* widget, int row, int column, QTableWidgetItem* item){
        this->lock = true;
        widget->setItem(row, column, item);
        this->lock = false;
    }

    void Dialog::lockedChangeContent(QTableWidget* widget, int row, int column, const QString& str){
        this->lock = true;
        widget->item(row, column)->setText(str);
        this->lock = false;
    }

    void Dialog::lockedChangeContent(QTableWidgetItem* item, const QString& str){
        this->lock = true;
        item->setText(str);
        this->lock = false;
    }
    void Dialog::closeEvent(QCloseEvent*){
        this->deleteLater();
    }

    void Dialog::cleanTable(QTableWidget* table){
        while(table->rowCount() > 0)
            table->removeRow(0);
    }

    void Dialog::setRowDisable(QTableWidget* table, int row){
        for(int column = 0; column < table->columnCount(); ++column){
            auto item = table->item(row, column);
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        }
    }

    void Dialog::setItemDisable(QTableWidget* table, int row, int column){
        auto item = table->item(row, column);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    }

    void Dialog::addItem(QTableWidget* table, const int& row, const int& column, const QString& str){
        QTableWidgetItem *item = new QTableWidgetItem(str);
        this->lockedChangeContent(table, row, column, item);
        this->tableMap[table]->insert(str, row, column);
    }

    void Dialog::addItem(QTableWidget* table, const int& row, const int& column, QTableWidgetItem* item){
        this->lockedChangeContent(table, row, column, item);
        this->tableMap[table]->insert(item->text(), row, column);
    }
}
