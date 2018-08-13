#include <QtWidgets/QWidget>
#include "matrix.h"
#include "ui_matrix.h"

namespace Template{
    Matrix::Matrix(MainWindow* window) : Template::MathContent(window),
        contentUi(new Ui::Matrix), contentWidget(this){

    }

    Matrix::~Matrix(){
        delete this->contentUi;
    }

    void Matrix::setup(){
        SETUP_UI(contentUi, contentWidget);
        this->installMenu();
    }

    void Matrix::buttonConnect(){

    }

    void Matrix::refresh(){

    }

    void Matrix::installMenu(){

    }

}
