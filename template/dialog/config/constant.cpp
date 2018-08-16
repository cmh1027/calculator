#include <QString>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include "constant.h"
#include "ui_constant.h"
#include "../../../config/config.h"
#include "../../../module/utility.h"

extern Configuration::Configuration* config;

namespace Dialog{
    Constant::Constant() : contentUi(new Ui::Constant), doubleList(config->getConstantList()),
        permanentDataTable(Column::Count), lock(false){
        contentUi->setupUi(this);
        this->permanentTable = this->findChild<QTableWidget*>("permanentConstantTableWidget");
        this->permanentDataTable = Table<QString>(this->permanentTable->columnCount());
        this->permanentTable->horizontalHeader()->setStretchLastSection(true);
        this->permanentTable->setCurrentItem(nullptr);
        this->installCells();
        connect(this->findChild<QToolButton*>("addButton"), &QPushButton::clicked, this, static_cast<void(Constant::*)()>(this->addItem));
        connect(this->findChild<QToolButton*>("deleteButton"), &QPushButton::clicked, this, this->removeItem);
    }

    Constant::~Constant(){
        delete contentUi;
    }

    void Constant::closeEvent(QCloseEvent*){
        this->deleteLater();
    }

    void Constant::installCells(){
        int permanent = 0;
        disconnect(this->permanentTable, &QTableWidget::itemChanged, nullptr, nullptr);
        while(this->permanentTable->rowCount() > 0)
            this->permanentTable->removeRow(0);
        this->permanentDataTable.rowClear();
        for(auto it = this->doubleList.begin(); it != this->doubleList.end(); it++){
            this->addItem(this->permanentTable, it.key(), (*it)->getDescription(),
                          Utility::doubleToString((*it)->getValue()),(*it)->getExpr(), permanent);

        }
        connect(this->permanentTable, &QTableWidget::itemChanged, [this](QTableWidgetItem* item){
            this->contentChanged(item, this->permanentTable, this->permanentDataTable);
        });
    }

    void Constant::contentChanged(QTableWidgetItem* item, QTableWidget* tableWidget, Table<QString>& table){
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
                    config->addConstant(text, this->doubleList.value(*table.at(item->row(), item->column())));
                    config->removeConstant(*table.at(item->row(), item->column()));
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
            }
            break;
        }
        config->refreshAllContents();
    }

    void Constant::lockedChangeContent(QTableWidget* widget, int row, int column, QTableWidgetItem* item){
        this->lock = true;
        widget->setItem(row, column, item);
        this->lock = false;
    }

    void Constant::lockedChangeContent(QTableWidget* widget, int row, int column, const QString& str){
        this->lock = true;
        widget->item(row, column)->setText(str);
        this->lock = false;
    }

    void Constant::lockedChangeContent(QTableWidgetItem* item, const QString& str){
        this->lock = true;
        item->setText(str);
        this->lock = false;
    }

    void Constant::updateRows(){
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

    void Constant::addItem(QTableWidget* table, const QString& symbol, const QString& description,
                                const QString& value, const QString& expr, int& index){
        table->setRowCount(table->rowCount() + 1);
        this->addItem(index, Column::Symbol, table, symbol);
        this->addItem(index, Column::Description, table, description);
        this->addItem(index, Column::Value, table, value);
        this->addItem(index, Column::Expression, table, expr);
        ++index;
    }

    void Constant::addItem(QTableWidget* table, const QString& symbol, const QString& description,
                                const QString& value, const QString& expr, int&& index){
        table->setRowCount(table->rowCount() + 1);
        this->addItem(index, Column::Symbol, table, symbol);
        this->addItem(index, Column::Description, table, description);
        this->addItem(index, Column::Value, table, value);
        this->addItem(index, Column::Expression, table, expr);
    }

    void Constant::addItem(const int& row, const int& column, QTableWidget* table, const QString& str){
        QTableWidgetItem *item = new QTableWidgetItem(str);
        this->lockedChangeContent(table, row, column, item);
        this->permanentDataTable.insert(str, row, column);
    }

    void Constant::addItem(){
        QString symbol = "{new%1}";
        int number = 0;
        while(this->doubleList.contains(symbol.arg(QString::number(number))))
            ++number;
        symbol = symbol.arg(QString::number(number));
        config->addConstant(symbol, new Const::ConstObject(0, false, false, ""));
        this->addItem(this->permanentTable, symbol, "", "0", "", this->permanentTable->rowCount());
    }

    void Constant::removeItem(){
        int row = this->permanentTable->currentRow();
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
