#include <QString>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include "function_dialog.h"
#include "ui_function_dialog.h"
#include "../../../config/config.h"
#include "../../../module/utility.h"

extern Configuration::Configuration* config;

namespace Dialog{
    Function::Function() : Dialog::Dialog(), contentUi(new Ui::Function), funcList(config->getFuncList()),
        permanentDataTable(Column::Count){
        contentUi->setupUi(this);
        INIT_TABLE(this->permanentTable, "permanentFunctionTableWidget", this->permanentDataTable);
        this->permanentTable->setColumnWidth(Column::Symbol, 60);
        this->permanentTable->setColumnWidth(Column::Arity, 80);
        this->permanentTable->setColumnWidth(Column::Blank, 60);
        this->installCells();
        connect(this->findChild<QToolButton*>("addButton"), &QPushButton::clicked, this, static_cast<void(Function::*)()>(this->addItem));
        connect(this->findChild<QToolButton*>("deleteButton"), &QPushButton::clicked, this, this->removeItem);
    }

    Function::~Function(){
        delete contentUi;
    }


    void Function::installCells(){
        int permanent = 0;
        disconnect(this->permanentTable, &QTableWidget::itemChanged, nullptr, nullptr);
        this->cleanTable(this->permanentTable);
        this->permanentDataTable.rowClear();
        for(auto it = this->funcList.begin(); it != this->funcList.end(); it++){
            this->addItem(this->permanentTable, it.key(), (*it), permanent);
            if((*it).isDefault())
                this->setRowDisable(this->permanentTable, permanent-1);
        }
        connect(this->permanentTable, &QTableWidget::itemChanged, [this](QTableWidgetItem* item){
            this->contentChanged(item, this->permanentTable, this->permanentDataTable);
        });
    }

    void Function::contentChanged(QTableWidgetItem* item, QTableWidget* tableWidget, Table<QString>& table){
        /*
        if(lock)
            return;
        QString &&text = item->text();
        auto constObject = this->funcList.value(*table.at(item->row(), Column::Symbol));
        switch(item->column()){
            case Column::Symbol:{
                if(text.indexOf("{") != 0 || text.indexOf("}") != text.length()-1 || text.mid(1, text.length()-2).isEmpty()
                        || this->funcList.contains(text) || text.mid(1).indexOf("{") != -1)
                    this->lockedChangeContent(item, *table.at(item->row(), item->column()));
                else{
                    config->addConstant(text, this->funcList.value(*table.at(item->row(), item->column())));
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
                    if(this->funcList.contains(key)){
                       auto object = this->funcList.value(key);
                       if(object->getExpr().indexOf(tableWidget->item(item->row(), Column::Symbol)->text()) != -1){
                           this->lockedChangeContent(item, *table.at(item->row(), item->column()));
                           return;
                       }
                    }
                    expr = expr.mid(back+1);
                }
                constObject->setExpr(item->text(), this->funcList);
                this->updateRows();
            }
            break;
        }
        config->refreshAllContents();
        */
    }


    void Function::addItem(QTableWidget* table, const QString& symbol, const Operation::OperationObject& object, int& index){
        table->setRowCount(table->rowCount() + 1);
        Dialog::addItem(table, index, Column::Symbol, symbol);
        Dialog::addItem(table, index, Column::Description, object.getDescription());
        this->setArityTableItem(table, index, Column::Arity, object.getArity());
        Dialog::addItem(table, index, Column::Blank, object.funcShape(symbol));
        Dialog::addItem(table, index, Column::Expression, object.getExpr());
        this->setItemDisable(table, index, Column::Blank);
        ++index;
    }

    void Function::addItem(QTableWidget* table, const QString& symbol, const Operation::OperationObject& object, int&& index){
        table->setRowCount(table->rowCount() + 1);
        Dialog::addItem(table, index, Column::Symbol, symbol);
        Dialog::addItem(table, index, Column::Description, object.getDescription());
        this->setArityTableItem(table, index, Column::Arity, object.getArity());
        Dialog::addItem(table, index, Column::Blank, object.funcShape(symbol));
        Dialog::addItem(table, index, Column::Expression, object.getExpr());
        this->setItemDisable(table, index, Column::Blank);
    }

    void Function::setArityTableItem(QTableWidget* table, int row, int column, Operation::Arity arity){
        switch(arity){
            case Operation::Arity::Arithmetic: {
                table->setItem(row, column, new QTableWidgetItem("Arithmetic"));
                return;
            }
            case Operation::Arity::Unary: {
                QComboBox* comboBox = new QComboBox();
                comboBox->insertItem(0, "Unary");
                comboBox->insertItem(1, "Binary");
                comboBox->setCurrentIndex(0);
                table->setCellWidget(row, column, comboBox);
                return;
            }
            case Operation::Arity::Binary:{
                QComboBox* comboBox = new QComboBox();
                comboBox->insertItem(0, "Unary");
                comboBox->insertItem(1, "Binary");
                comboBox->setCurrentIndex(1);
                table->setCellWidget(row, column, comboBox);
                return;
            }
            default:{
                table->setItem(row, column, new QTableWidgetItem());
                return;
            }
        }
    }

    void Function::addItem(){
        QString symbol = "new%1";
        int number = 0;
        while(this->funcList.contains(symbol.arg(QString::number(number))))
            ++number;
        symbol = symbol.arg(QString::number(number));
        config->addFunction(symbol, Operation::OperationObject("", "", Operation::Arity::Unary));
        this->addItem(this->permanentTable, symbol, *object, this->permanentTable->rowCount());
    }


    void Function::removeItem(){
        int row = this->permanentTable->currentRow();
        if(this->funcList.value(this->permanentTable->item(row, Column::Symbol)->text()).isDefault()){
            QMessageBox::critical(this, "error", "Default function can not be deleted");
        }
        else{
            config->removeFunction(this->permanentTable->item(row, Column::Symbol)->text());
            this->permanentTable->removeRow(row);
            this->permanentDataTable.removeRow(row);
        }
    }
}
