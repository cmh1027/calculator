#ifndef SCIENTIFIC_H
#define SCIENTIFIC_H
#include "../general/general.h"

class MainWindow;

namespace Ui {
    class ScientificCalculator;
}

namespace Template{
    class ScientificCalculator : public Template::GeneralCalculator
    {
        Q_OBJECT

    public:
        ScientificCalculator(MainWindow*);
        virtual ~ScientificCalculator();
        void setup() override;
        void binarySpecial(const QString &format);

    private:
        Ui::ScientificCalculator *contentUi;
        QWidget *contentWidget;
        enum Mode {One, Two, Length};
        using Mode = enum Mode;
        int screen;
        void buttonConnect() override;

    protected:
        void change();
        void cube();
        void root();
        void pow();
        void sin();
        void cos();
        void tan();
        void asin();
        void acos();
        void atan();
        void sinh();
        void cosh();
        void tanh();
        void log();
        void ln();
        void mod();
        void fac();
        void abs();
        void pi();
        void e();
        CMap<QString, void(ScientificCalculator::*)()> Operators;

    public slots:
        void buttonPushed() override;
    };
}
#endif // SCIENTIFIC_H
