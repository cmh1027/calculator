#ifndef GRAPH_H
#define GRAPH_H
#include "../mathcontent.h"

namespace Ui{
    class Graph;
}
class QWidget;

namespace Template{
    class Graph : public Template::MathContent
    {
        Q_OBJECT

    public:
        Graph(MainWindow*);
        virtual ~Graph();
        void setup() override;

    private:
        Ui::Graph *contentUi;
        QWidget *contentWidget;
        void buttonConnect() override;
        void installMenu() override;
    };
}

#endif // GRAPH_H
