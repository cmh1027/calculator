#include <QtWidgets/QWidget>
#include "graph.h"
#include "ui_graph.h"

namespace Template{
    Graph::Graph(MainWindow* window) : Template::MathContent(window),
        contentUi(new Ui::Graph), contentWidget(this){

    }

    Graph::~Graph(){
        delete this->contentUi;
    }

    void Graph::setup(){
        SETUP_UI(contentUi, contentWidget)
    }

    void Graph::buttonConnect(){

    }

    void Graph::installMenu(){

    }


}
