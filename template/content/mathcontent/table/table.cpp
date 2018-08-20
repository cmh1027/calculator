#include <QtWidgets/QWidget>
#include "table.h"
#include "ui_table.h"

namespace Template{
    Table::Table(MainWindow* window) : Template::MathContent(window),
        contentUi(new Ui::Table), contentWidget(this){

    }

    Table::~Table(){
        delete this->contentUi;
    }

    void Table::setup(){
        this->setupUi(this, this->contentUi, this->contentWidget);
        this->installMenu();
    }

    void Table::buttonConnect(){

    }

    void Table::refresh(){

    }

    void Table::installMenu(){

    }

}
