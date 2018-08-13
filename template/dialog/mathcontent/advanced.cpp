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
        contentUi(new Ui::Advanced), doubleList(const_cast<CMap<QString, Const::ConstObject>&>(mathContent->getDoubleList())){
        contentUi->setupUi(this);
        int temp = 0;
        int permanent = 0;
        this->tempTable = this->findChild<QTableWidget*>("tempConstantTableWidget");
        this->permanentTable = this->findChild<QTableWidget*>("permanentConstantTableWidget");
        this->tempTable->horizontalHeader()->setStretchLastSection(true);
        this->permanentTable->horizontalHeader()->setStretchLastSection(true);
        for(auto it = doubleList.begin(); it != doubleList.end(); it++){
            if((*it).isTemp()){
                this->addTemp(it.key(), Utility::doubleToString((*it).getValue()), (*it).getDescription(), temp);
            }
            else{
                this->addPermanent(it.key(), Utility::doubleToString((*it).getValue()), (*it).getDescription(), permanent);
            }
        }
        connect(this->findChild<QToolButton*>("deleteButton"), &QPushButton::clicked, this, this->removeItem);
    }

    Advanced::~Advanced(){
        delete contentUi;
        tempTable->clear();
        permanentTable->clear();
    }

    void Advanced::closeEvent(QCloseEvent*){
        this->deleteLater();
    }

    void Advanced::addTemp(const QString& symbol, const QString& value, const QString& description, int &index){
        QTableWidgetItem *item;
        this->tempTable->setRowCount(this->tempTable->rowCount() + 1);
        item = new QTableWidgetItem(symbol);
        this->tempTable->setItem(index, 0, item);
        item = new QTableWidgetItem(value);
        this->tempTable->setItem(index, 1, item);
        item = new QTableWidgetItem(description);
        this->tempTable->setItem(index, 2, item);
        ++index;
        this->tempTable->setRowCount(index);
    }

    void Advanced::addPermanent(const QString& symbol, const QString& value, const QString& description, int& index){
        QTableWidgetItem *item;
        this->permanentTable->setRowCount(this->permanentTable->rowCount() + 1);
        item = new QTableWidgetItem(symbol);
        this->permanentTable->setItem(index, 0, item);
        item = new QTableWidgetItem(value);
        this->permanentTable->setItem(index, 1, item);
        item = new QTableWidgetItem(description);
        this->permanentTable->setItem(index, 2, item);
        ++index;
    }

    void Advanced::addItem(){

    }

    void Advanced::removeItem(){
        int row;
        if((row = this->tempTable->currentRow()) != -1){
            this->mainWindow->removeConstant(this->tempTable->itemAt(0, row)->text());
            this->tempTable->removeRow(row);
        }
        else if((row = this->permanentTable->currentRow()) != -1){
            if(this->doubleList.value(this->permanentTable->itemAt(0, row)->text()).isDefault()){
                QMessageBox::critical(this, "error", "Default constant can not be deleted");
            }
            else{
                this->mainWindow->removeConstant(this->permanentTable->itemAt(0, row)->text());
                this->permanentTable->removeRow(row);
            }
        }
    }
}
