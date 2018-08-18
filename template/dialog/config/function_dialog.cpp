#include <QString>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QRegExp>
#include "function_dialog.h"
#include "ui_function_dialog.h"
#include "../../../config/config.h"
#include "../../../module/utility.h"
extern Configuration::Configuration* config;

namespace Dialog{
    Function::Function() : Dialog::Dialog(this), contentUi(new Ui::Function), funcList(config->getFuncList()),
        permanentDataTable(Column::Count){
        contentUi->setupUi(this);
        this->tableInitialize(this->permanentTable, "permanentFunctionTableWidget", this->permanentDataTable);
        this->permanentTable->setColumnWidth(Column::Symbol, 60);
        this->permanentTable->setColumnWidth(Column::Arity, 80);
        this->permanentTable->setColumnWidth(Column::Blank, 60);
        this->installCells();
        connect(this->findChild<QToolButton*>("addButton"), &QPushButton::clicked, this, static_cast<void(Function::*)()>(this->addItem));
        connect(this->findChild<QToolButton*>("deleteButton"), &QPushButton::clicked, this, this->removeItem);
        connect(this->findChild<QToolButton*>("xButton"), &QPushButton::clicked, this, this->x);
        connect(this->findChild<QToolButton*>("yButton"), &QPushButton::clicked, this, this->y);
    }

    Function::~Function(){
        delete contentUi;
    }


    void Function::installCells(){
        int permanent = 0;
        this->disableChangeEvent();
        this->cleanTable(this->permanentTable);
        this->permanentDataTable.rowClear();
        for(auto it = this->funcList.begin(); it != this->funcList.end(); it++){
            this->addItem(this->permanentTable, it.key(), (*it), permanent);
            if((*it)->isDefault())
                this->setRowDisable(this->permanentTable, permanent-1);
        }
        this->enableChangeEvent();
    }

    void Function::contentChanged(QTableWidgetItem* item, QTableWidget* tableWidget, Table<QString>& table){
        QString &&text = item->text();
        auto funcObject = this->funcList.value(*table.at(item->row(), Column::Symbol));
        QString str = *table.at(item->row(), item->column());
        switch(item->column()){
            case Column::Symbol:{
                if(!QRegExp("[A-Za-z]*").exactMatch(text))
                    this->changeWithoutEvent(item, str);
                else{
                    config->addFunction(text, funcObject);
                    config->removeFunction(str);
                }
            }
            break;
            case Column::Description:{
                funcObject->setDescription(item->text());
                table.insert(item->text(), item->row(), item->column());
            }
            break;
            case Column::Arity:{
                Q_ASSERT(false);
            }
            break;
            case Column::Expression:{
                QString &&expr = item->text();
                QString &&key = "";
                int front = 0;
                for(int index = 0; index < expr.length(); ++index){
                    if(!expr.at(index).isLower() && !expr.at(index).isUpper()){
                        key = expr.mid(front, index-front);
                        if(this->funcList.contains(key)){
                            auto object = this->funcList.value(key);
                            if(object->getExpr().indexOf(tableWidget->item(item->row(), Column::Symbol)->text()) != -1){
                                this->changeWithoutEvent(item, str);
                                return;
                            }
                        }
                        front = index+1;
                    }
                }
                funcObject->setExpr(item->text());
            }
            break;
        }
        config->refreshAllContents();
    }


    void Function::addItem(QTableWidget* table, const QString& symbol, Operation::OperationObject* object, int& index){
        table->setRowCount(table->rowCount() + 1);
        Dialog::addItem(table, index, Column::Symbol, symbol);
        Dialog::addItem(table, index, Column::Description, object->getDescription());
        this->setArityTableItem(table, index, Column::Arity, object);
        Dialog::addItem(table, index, Column::Blank, object->funcShape(symbol));
        Dialog::addItem(table, index, Column::Expression, object->getExpr());
        this->setItemDisable(table, index, Column::Blank);
        ++index;
    }

    void Function::addItem(QTableWidget* table, const QString& symbol, Operation::OperationObject* object, int&& index){
        table->setRowCount(table->rowCount() + 1);
        Dialog::addItem(table, index, Column::Symbol, symbol);
        Dialog::addItem(table, index, Column::Description, object->getDescription());
        this->setArityTableItem(table, index, Column::Arity, object);
        Dialog::addItem(table, index, Column::Blank, object->funcShape(symbol));
        Dialog::addItem(table, index, Column::Expression, object->getExpr());
        this->setItemDisable(table, index, Column::Blank);
    }

    void Function::setArityTableItem(QTableWidget* table, int row, int column, Operation::OperationObject* object){
        this->disableChangeEvent();
        switch(object->getArity()){
            case Operation::Arity::Arithmetic: {
                table->setItem(row, column, new QTableWidgetItem("Arithmetic"));
            }
            break;
            case Operation::Arity::Unary: {
                QComboBox* comboBox = new QComboBox();
                comboBox->insertItem(0, "Unary");
                comboBox->insertItem(1, "Binary");
                comboBox->setCurrentIndex(0);
                connect(comboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, [=](int index){
                    object->setArity(static_cast<Operation::Arity>(index+1));
                    auto item = table->item(row, Column::Expression);
                    QString &&str = item->text();
                    if(str.indexOf(Operation::Unknown::Y) != -1){
                        item->setText("");
                    }
                });
                table->setCellWidget(row, column, comboBox);
            }
            break;
            case Operation::Arity::Binary:{
                QComboBox* comboBox = new QComboBox();
                comboBox->insertItem(0, "Unary");
                comboBox->insertItem(1, "Binary");
                comboBox->setCurrentIndex(1);
                connect(comboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, [=](int index){
                    object->setArity(static_cast<Operation::Arity>(index+1));
                });
                table->setCellWidget(row, column, comboBox);
            }
            break;
            default:{
                table->setItem(row, column, new QTableWidgetItem());
            }
            break;
        }
        this->enableChangeEvent();
    }

    void Function::addItem(){
        QString &&symbol = "a";
        while(this->funcList.contains(symbol)){
            symbol = symbol + "a";
        }
        auto object = new Operation::OperationObject("", "", Operation::Arity::Unary);
        config->addFunction(symbol, object);
        this->installCells();
    }


    void Function::removeItem(){
        int row = this->permanentTable->currentRow();
        if(this->funcList.value(this->permanentTable->item(row, Column::Symbol)->text())->isDefault()){
            QMessageBox::critical(this, "error", "Default function can not be deleted");
        }
        else{
            config->removeFunction(this->permanentTable->item(row, Column::Symbol)->text());
            this->permanentTable->removeRow(row);
            this->permanentDataTable.removeRow(row);
        }
    }

    void Function::x(){
        int row = this->permanentTable->currentRow();
        int column = this->permanentTable->currentColumn();
        if(row == -1 || column == -1)
            return;
        auto item = this->permanentTable->item(row, column);
        auto object = this->funcList.value(this->permanentTable->item(row, Column::Symbol)->text());
        QString &&str = item->text();
        if(column != Column::Expression || object->isDefault())
            return;
        if(!str.isEmpty() && (str.back() == Operation::Unknown::X || str.back() == Operation::Unknown::Y))
            return;
        item->setText(str + Operation::Unknown::X);
    }

    void Function::y(){
        int row = this->permanentTable->currentRow();
        int column = this->permanentTable->currentColumn();
        if(row == -1 || column == -1)
            return;
        auto item = this->permanentTable->item(row, column);
        auto object = this->funcList.value(this->permanentTable->item(row, Column::Symbol)->text());
        QString &&str = item->text();
        if(column != Column::Expression || object->isDefault() || object->getArity() < Operation::Arity::Binary)
            return;
        if(!str.isEmpty() && (str.back() == Operation::Unknown::X || str.back() == Operation::Unknown::Y))
            return;
        item->setText(str + Operation::Unknown::Y);
    }
}
