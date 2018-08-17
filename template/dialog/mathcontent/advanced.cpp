#include <QString>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include "advanced.h"
#include "ui_advanced.h"
#include "../../content/mathcontent/mathcontent.h"
#include "../../../config/config.h"
#include "../../../module/utility.h"
#include <iostream>
extern Configuration::Configuration* config;

namespace Dialog{
    Advanced::Advanced(Template::MathContent* mathContent) : Dialog::Dialog(), parent(mathContent),
        contentUi(new Ui::Advanced), doubleList(mathContent->getDoubleList()),
        tempDataTable(Column::Count), permanentDataTable(Column::Count){
        contentUi->setupUi(this);
        INIT_TABLE(this->tempTable, "tempConstantTableWidget", this->tempDataTable);
        INIT_TABLE(this->permanentTable, "permanentConstantTableWidget", this->permanentDataTable);
        this->installCells();
        connect(this->tempTable, &QTableWidget::currentItemChanged, this, [this]{
           this->permanentTable->setCurrentItem(nullptr);
        });
        connect(this->permanentTable, &QTableWidget::currentItemChanged, this, [this]{
           this->tempTable->setCurrentItem(nullptr);
        });
        connect(this->findChild<QToolButton*>("addButton"), &QPushButton::clicked, this, static_cast<void(Advanced::*)()>(this->addItem));
        connect(this->findChild<QToolButton*>("promoteButton"), &QPushButton::clicked, this, this->promoteItem);
        connect(this->findChild<QToolButton*>("deleteButton"), &QPushButton::clicked, this, this->removeItem);
    }

    Advanced::~Advanced(){
        delete contentUi;
    }

    void Advanced::installCells(){
        int temp = 0;
        int permanent = 0;
        disconnect(this->tempTable, &QTableWidget::itemChanged, nullptr, nullptr);
        disconnect(this->permanentTable, &QTableWidget::itemChanged, nullptr, nullptr);
        this->cleanTable(this->tempTable);
        this->cleanTable(this->permanentTable);
        this->tempDataTable.rowClear();
        this->permanentDataTable.rowClear();
        for(auto it = this->doubleList.begin(); it != this->doubleList.end(); it++){
            if((*it)->isTemp()){
                this->addItem(this->tempTable, it.key(), (*it), temp);
            }
            else{
                this->addItem(this->permanentTable, it.key(), (*it), permanent);
                if((*it)->isDefault())
                    this->setRowDisable(this->permanentTable, permanent-1);
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
        auto constObject = this->doubleList.value(*table.at(item->row(), Column::Symbol));
        switch(item->column()){
            case Column::Symbol:{
                if(text.indexOf("{") != 0 || text.indexOf("}") != text.length()-1 || text.mid(1, text.length()-2).isEmpty()
                        || this->doubleList.contains(text) || text.mid(1).indexOf("{") != -1)
                    this->lockedChangeContent(item, *table.at(item->row(), item->column()));
                else{
                    if(tableWidget == this->tempTable){
                        this->doubleList[text] = this->doubleList.clone(*table.at(item->row(), item->column()));
                        this->doubleList.remove(*table.at(item->row(), item->column()));
                        this->parent->refresh();
                    }
                    else{
                        config->addConstant(text, this->doubleList.clone(*table.at(item->row(), item->column())));
                        config->removeConstant(*table.at(item->row(), item->column()));
                    }
                    this->updateRows();
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
                    if(constObject->isTemp())
                        this->parent->refresh();
                    else
                        config->refreshAllContents();
                }
                else
                    this->lockedChangeContent(item, *table.at(item->row(), item->column()));
            }
            break;
            case Column::Expression:{
                QString &&expr = item->text();
                QString &&key = "";
                int front, back;
                while((front = expr.indexOf("{")) != -1 && (back = expr.indexOf("}")) != -1){
                    key = expr.mid(front, back-front+1);
                    if(this->doubleList.contains(key)){
                       auto object = this->doubleList.value(key);
                       if(object->getExpr().indexOf(tableWidget->item(item->row(), Column::Symbol)->text()) != -1){
                           this->lockedChangeContent(item, *table.at(item->row(), item->column()));
                           return;
                       }
                    }
                    expr = expr.mid(back+1);
                }
                constObject->setExpr(item->text(), this->doubleList);
                this->updateRows();
                if(constObject->isTemp())
                    this->parent->refresh();
                else
                    config->refreshAllContents();
            }
            break;
        }
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

    void Advanced::addItem(QTableWidget* table, const QString& symbol, const Const::ConstObject* object, int& index){
        table->setRowCount(table->rowCount() + 1);
        Dialog::addItem(table, index, Column::Symbol, symbol);
        Dialog::addItem(table, index, Column::Description, object->getDescription());
        Dialog::addItem(table, index, Column::Value, Utility::doubleToString(object->getValue()));
        Dialog::addItem(table, index, Column::Expression, object->getExpr());
        ++index;
    }

    void Advanced::addItem(QTableWidget* table, const QString& symbol, const Const::ConstObject* object, int&& index){
        table->setRowCount(table->rowCount() + 1);
        Dialog::addItem(table, index, Column::Symbol, symbol);
        Dialog::addItem(table, index, Column::Description, object->getDescription());
        Dialog::addItem(table, index, Column::Value, Utility::doubleToString(object->getValue()));
        Dialog::addItem(table, index, Column::Expression, object->getExpr());
    }

    void Advanced::addItem(){
        QString symbol = "{new%1}";
        int number = 0;
        while(this->doubleList.contains(symbol.arg(QString::number(number))))
            ++number;
        symbol = symbol.arg(QString::number(number));
        auto object = new Const::ConstObject(0, false, false, "");
        config->addConstant(symbol, object);
        this->addItem(this->permanentTable, symbol, object, this->permanentTable->rowCount());
    }

    void Advanced::removeItem(){
        int row;
        if((row = this->tempTable->currentRow()) != -1){
            this->doubleList.remove(this->tempTable->item(row, Column::Symbol)->text());
            this->tempTable->removeRow(row);
            this->tempDataTable.removeRow(row);
        }
        else if((row = this->permanentTable->currentRow()) != -1){
            if(this->doubleList.value(this->permanentTable->item(row, Column::Symbol)->text())->isDefault()){
                QMessageBox::critical(this, "error", "Default constant can not be deleted");
            }
            else{
                config->removeConstant(this->permanentTable->item(row, Column::Symbol)->text());
                this->permanentTable->removeRow(row);
                this->permanentDataTable.removeRow(row);
            }
        }
    }

    void Advanced::promoteItem(){
        int row;
        if((row = this->tempTable->currentRow()) != -1){
            QString &&key = this->tempTable->item(row, Column::Symbol)->text();
            auto object = this->doubleList.clone(key);
            object->setTemp(false);
            this->doubleList.remove(key);
            config->addConstant(key, object);
            this->updateRows();
        }
    }

}
