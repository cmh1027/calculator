#ifndef MATRIX_H
#define MATRIX_H
#include "../mathcontent.h"

namespace Ui{
    class Matrix;
}
class QWidget;

namespace Template{
    class Matrix : public Template::MathContent
    {
        Q_OBJECT

    public:
        Matrix(MainWindow*);
        virtual ~Matrix();
        void setup() override;
        void refresh() override;

    private:
        Ui::Matrix *contentUi;
        QWidget *contentWidget;
        void buttonConnect() override;
        void installMenu() override;
    };
}
#endif // MATRIX_H
