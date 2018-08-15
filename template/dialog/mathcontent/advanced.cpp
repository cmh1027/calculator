#include <QString>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include "advanced.h"
#include "ui_advanced.h"
#include "../../mainwindow.h"
#include "../../content/mathcontent/mathcontent.h"
#include "../../../config/config.h"
#include "../../../module/utility.h"

extern Configuration* config;

namespace Dialog{
    Advanced::Advanced(Template::MathContent* mathContent, MainWindow* window) : mainWindow(window), parent(mathContent),
        contentUi(new Ui::Advanced), doubleList(mathContent->getDoubleList()),
        tempDataTable(Column::Count), permanentDataTable(Column::Count), lock(false){
        contentUi->setupUi(this);
        this->tempTable = this->findChild<QTableWidget*>("tempConstantTableWidget");
        this->permanentTable = this->findChild<QTableWidget*>("permanentConstantTableWidget");
        this->tempDataTable = Table<QString>(this->tempTable->columnCount());
        this->permanentDataTable = Table<QString>(this->permanentTable->columnCount());
        this->tempTable->horizontalHeader()->setStretchLastSection(true);
        this->permanentTable->horizontalHeader()->setStretchLastSection(true);
        this->tempTable->setCurrentItem(nullptr);
        this->permanentTable->setCurrentItem(nullptr);
        connect(this->tempTable, &QTableWidget::currentItemChanged, this, [this]{
           this->permanentTable->setCurrentItem(nullptr);
        });
        connect(this->permanentTable, &QTableWidget::currentItemChanged, this, [this]{
           this->tempTable->setCurrentItem(nullptr);
        });
        this->installCells();
        connect(this->findChild<QToolButton*>("addButton"), &QPushButton::clicked, this, static_cast<void(Advanced::*)()>(this->addItem));
        connect(this->findChild<QToolButton*>("deleteButton"), &QPushButton::clicked, this, this->removeItem);
    }

    Advanced::~Advanced(){
        delete contentUi;
    }

    void Advanced::closeEvent(QCloseEvent*){
        this->deleteLater();
    }

    void Advanced::installCells(){
        int temp = 0;
        int permanent = 0;
        disconnect(this->tempTable, &QTableWidget::itemChanged, nullptr, nullptr);
        disconnect(this->permanentTable, &QTableWidget::itemChanged, nullptr, nullptr);
        while(this->tempTable->rowCount() > 0)
            this->tempTable->removeRow(0);
        while(this->permanentTable->rowCount() > 0)
            this->permanentTable->removeRow(0);
        this->tempDataTable.rowClear();
        this->permanentDataTable.rowClear();
        for(auto it = this->doubleList.begin(); it != this->doubleList.end(); it++){
            if((*it)->isTemp()){
                this->addItem(this->tempTable, it.key(), (*it)->getDescription(),
                              Utility::doubleToString((*it)->getValue()), (*it)->getExpr(), temp);
            }
            else{
                this->addItem(this->permanentTable, it.key(), (*it)->getDescription(),
                              Utility::doubleToString((*it)->getValue()),(*it)->getExpr(), permanent);
            }
        }
        connect(this->tempTable, &QTableWidget::itemChanged, [this](QTableWidgetItem* item){
            this->contentChanged(item, this->tempTable, this->tempDataTable);
        });
        connect(this->permanentTable, &QTableWidget::itemChanged, [this](QTableWidgetItem* item){
            this->contentChanged(item, this->permanentTable, this->permanentDataTable);
        });
    }

    void Advanced::contentChanged(QTableWidgetItem* item, QTableWidget* tableWidget, Table<QString>& table){
        if(lock)
            return;
        QString &&text = item->text();
        auto constObject = this->doubleList.value(tableWidget->item(item->row(), Column::Symbol)->text());
        switch(item->column()){
            case Column::Symbol:{
                if(text.indexOf("{") != 0 || text.indexOf("}") != text.length()-1 || text.mid(1, text.length()-2).isEmpty()
                        || this->doubleList.contains(text) || text.mid(1).indexOf("{") != -1)
                    this->lockedChangeContent(item, *table.at(item->row(), item->column()));
                else{
                    if(tableWidget == this->tempTable){
                        this->doubleList[text] = this->doubleList.value(*table.at(item->row(), item->column()));
                        this->doubleList.remove(*table.at(item->row(), item->column()));
                        this->parent->refresh();
                    }
                    else{
                        config->addConstant(text, this->doubleList.value(*table.at(item->row(), item->column())));
                        config->removeConstant(*table.at(item->row(), item->column()));
                    }
                    table.insert(text, item->row(), item->column());
                }
            }
            break;
            case Column::Description:{
                constObject->setDescription(item->text());
                table.insert(item->text(), item->row(), item->column());
            }
            break;
            case Column::Value:{
                bool isDouble;
                double value = item->text().toDouble(&isDouble);
                if(isDouble){
                    constObject->setValue(value);
                    this->updateRows();
                    this->parent->refresh();
                }
                else
                    this->lockedChangeContent(item, *table.at(item->row(), item->column()));
            }
            break;
            case Column::Expression:{
                constObject->setExpr(item->text(), this->doubleList);
                this->updateRows();
                this->parent->refresh();
            }
            break;
        }
    }

    void Advanced::lockedChangeContent(QTableWidget* widget, int row, int column, const QString& str){
        lock = true;
        widget->item(row, column)->setText(str);
        lock = false;
    }

    void Advanced::lockedChangeContent(QTableWidgetItem* item, const QString& str){
        lock = true;
        item->setText(str);
        lock = false;
    }

    void Advanced::updateRows(){
        bool isUpdated = false;
        while(true){
            isUpdated = false;
            for(auto it = this->doubleList.begin(); it != this->doubleList.end(); ++it){
                isUpdated = (*it)->update(this->doubleList);
            }
            if(!isUpdated)
                break;
        }
        this->installCells();
    }

    void Advanced::addItem(QTableWidget* table, const QString& symbol, const QString& description,
                                const QString& value, const QString& expr, int& index){
        table->setRowCount(table->rowCount() + 1);
        this->addItem(index, Column::Symbol, table, symbol);
        this->addItem(index, Column::Description, table, description);
        this->addItem(index, Column::Value, table, value);
        this->addItem(index, Column::Expression, table, expr);
        ++index;
    }

    void Advanced::addItem(const int& row, const int& column, QTableWidget* table, const QString& str){
        QTableWidgetItem *item = new QTableWidgetItem(str);
        table->setItem(row, column, item);
        if(table == this->tempTable)
            this->tempDataTable.insert(str, row, column);
        else if(table == this->permanentTable)
            this->permanentDataTable.insert(str, row, column);
    }

    void Advanced::addItem(){

    }

    void Advanced::removeItem(){
        int row;
        if((row = this->tempTable->currentRow()) != -1){
            this->doubleList.remove(this->tempTable->itemAt(Column::Symbol, row)->text());
            this->tempTable->removeRow(row);
            this->tempDataTable.removeRow(row);
        }
        else if((row = this->permanentTable->currentRow()) != -1){
            if(this->doubleList.value(this->permanentTable->itemAt(Column::Symbol, row)->text())->isDefault()){
                QMessageBox::critical(this, "error", "Default constant can not be deleted");
            }
            else{
                config->removeConstant(this->permanentTable->itemAt(Column::Symbol, row)->text());
                this->permanentTable->removeRow(row);
                this->permanentDataTable.removeRow(row);
            }
        }
    }
}
