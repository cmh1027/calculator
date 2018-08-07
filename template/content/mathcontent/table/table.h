#ifndef TABLE_H
#define TABLE_H
#include "../mathcontent.h"

namespace Ui{
    class Table;
}
class QWidget;

namespace Template{
    class Table : public Template::MathContent
    {
        Q_OBJECT

    public:
        Table(MainWindow*);
        virtual ~Table();
        void setup() override;

    private:
        Ui::Table *contentUi;
        QWidget *contentWidget;
        void buttonConnect() override;
        void installMenu() override;
    };
}
#endif // TABLE_H
