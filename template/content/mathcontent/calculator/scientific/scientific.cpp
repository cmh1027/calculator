#include "scientific.h"
#include "ui_scientific.h"
#include "../../../../../module/calculator/operator.h"
#include "../../../../mainwindow.h"
#include "../../../../../module/ctl.h"

namespace Template{
    ScientificCalculator::ScientificCalculator(MainWindow* window) : Template::GeneralCalculator(window),
        contentUi(new Ui::ScientificCalculator), contentWidget(this->findChild<QWidget*>("buttonWidget")),
        screen(Mode::One)
    {
        for(auto iter = GeneralCalculator::Operators.constBegin(); iter != GeneralCalculator::Operators.constEnd(); ++iter){
            Operators[iter.key()] = iter.value();
        }
        Operators["cube"] = this->cube;
        Operators["root"] = this->root;
        Operators["pow"] = this->pow;
        Operators["sin"] = this->sin;
        Operators["cos"] = this->cos;
        Operators["tan"] = this->tan;
        Operators["asin"] = this->asin;
        Operators["acos"] = this->acos;
        Operators["atan"] = this->atan;
        Operators["sinh"] = this->sinh;
        Operators["cosh"] = this->cosh;
        Operators["tanh"] = this->tanh;
        Operators["log"] = this->log;
        Operators["ln"] = this->ln;
        Operators["mod"] = this->mod;
        Operators["fac"] = this->fac;
        Operators["abs"] = this->abs;
        Operators["pi"] = this->pi;
        Operators["e"] = this->e;
        Operators["change"] = this->change;
    }
    ScientificCalculator::~ScientificCalculator(){
        delete this->contentUi;
    }

    void ScientificCalculator::setup(){
        SETUP_UI_CAL(contentUi, contentWidget);
    }

    void ScientificCalculator::buttonConnect(){
        foreach(QPushButton* button, contentWidget->findChildren<QPushButton*>()){ \
            connect(button, &QPushButton::clicked, this, &this->buttonPushed); \
        }
    }

    void ScientificCalculator::buttonPushed(){
        if(this->isModifying)
            return;
        QRegExp rx("num[0-9]{1}Button");
        auto button = sender();
        QString buttonName = button->objectName();
        if(rx.exactMatch(buttonName)){
            this->addNumber(buttonName.mid(3, 1));
        }
        else{
            QString funcName = buttonName.chopped(6);
            if(this->Operators.contains(funcName))
                (this->*(this->Operators[funcName]))();
            else{
                Q_ASSERT(this->Operators.contains(funcName));
            }
        }
    }

    void ScientificCalculator::binarySpecial(const QString &op){
        if(this->getInter().isEmpty() || !this->calculated){
            this->appendInter(this->getResult());
            this->appendInter(op);
        }
        else{
            if(this->isLastOpArithmetic())
                this->replaceLastOp(op);
            else
                this->appendInter(op);
        }
        this->specialStart = true;
        this->calculated = false;
    }

    void ScientificCalculator::change(){
        screen = (screen + 1) % Mode::Length;
        if(screen == Mode::One){
            this->changeButton("cube", "sqr", "x²");
            this->changeButton("root", "pow", "xʸ");
            this->changeButton("asin", "sin", "sin");
            this->changeButton("acos", "cos", "cos");
            this->changeButton("atan", "tan", "tan");
            this->changeButton("inverse", "sqrt", "√");
            this->changeButton("fac", "abs", "｜x｜");
            this->changeButton("sinh", "log", "log");
            this->changeButton("cosh", "ln", "ln");
            this->changeButton("tanh", "mod", "mod");
        }
        else if(screen == Mode::Two){
            this->changeButton("sqr", "cube", "x³");
            this->changeButton("pow", "root", "ʸ√x");
            this->changeButton("sin", "asin", "sin⁻¹");
            this->changeButton("cos", "acos", "cos⁻¹");
            this->changeButton("tan", "atan", "tan⁻¹");
            this->changeButton("sqrt", "inverse", "1/x");
            this->changeButton("abs", "fac", "n!");
            this->changeButton("log", "sinh", "sinh");
            this->changeButton("ln", "cosh", "cosh");
            this->changeButton("mod", "tanh", "tanh");
        }
    }

    void ScientificCalculator::cube(){
        this->unarySpecial(Operator::Special::cube);
    }

    void ScientificCalculator::root(){
        this->binarySpecial(Operator::Special::root);
    }

    void ScientificCalculator::pow(){
        this->binarySpecial(Operator::Special::pow);
    }

    void ScientificCalculator::sin(){
        this->unarySpecial(Operator::Special::sin);
    }

    void ScientificCalculator::cos(){
        this->unarySpecial(Operator::Special::cos);
    }

    void ScientificCalculator::tan(){
        this->unarySpecial(Operator::Special::tan);
    }

    void ScientificCalculator::asin(){
        this->unarySpecial(Operator::Special::asin);
    }

    void ScientificCalculator::acos(){
        this->unarySpecial(Operator::Special::acos);
    }

    void ScientificCalculator::atan(){
        this->unarySpecial(Operator::Special::atan);
    }

    void ScientificCalculator::sinh(){
        this->unarySpecial(Operator::Special::sinh);
    }

    void ScientificCalculator::cosh(){
        this->unarySpecial(Operator::Special::cosh);
    }

    void ScientificCalculator::tanh(){
        this->unarySpecial(Operator::Special::tanh);
    }

    void ScientificCalculator::log(){
        this->unarySpecial(Operator::Special::log);
    }

    void ScientificCalculator::ln(){
        this->unarySpecial(Operator::Special::ln);
    }

    void ScientificCalculator::mod(){
        this->unarySpecial(Operator::Special::mod);
    }

    void ScientificCalculator::fac(){
        this->unarySpecial(Operator::Special::fac);
    }

    void ScientificCalculator::abs(){
        this->unarySpecial(Operator::Special::abs);
    }

    void ScientificCalculator::pi(){
        this->constant("{pi}");
    }

    void ScientificCalculator::e(){
        this->constant("{e}");
    }
}
