#ifndef SCIENTIFIC_H
#define SCIENTIFIC_H
#include "../general/general.h"

namespace Ui {
    class Form;
}

class ScientificCalculator : public GeneralCalculator{
    Q_OBJECT

public:
    ScientificCalculator(QMainWindow*);
    virtual ~ScientificCalculator();
    void setup() override;

private:
    Ui::Form *contentUi;
    QMainWindow *MainWindow;

protected:
    void binarySpecial(const QString &format);
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
    void mod();
    void fac();

};

#endif // SCIENTIFIC_H
