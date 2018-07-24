#include "general.h"
#include "ui_general.h"

GeneralCalculator::GeneralCalculator(QMainWindow *window) :
    contentUi(new Ui::Form), MainWindow(window), calculated(false), specialStart(false),
    Operators(std::initializer_list<std::pair<QString, void(GeneralCalculator::*)()>>({
        std::make_pair("plus", this->plus), std::make_pair("minus", this->minus), std::make_pair("multiply", this->multiply),
        std::make_pair("divide", this->divide), std::make_pair("equal", this->equal), std::make_pair("erase", this->erase),
        std::make_pair("dot", this->dot), std::make_pair("negate", this->negate), std::make_pair("ce", this->ce),
        std::make_pair("c", this->c), std::make_pair("percent", this->percent), std::make_pair("sqrt", this->sqrt),
        std::make_pair("sqr", this->sqr), std::make_pair("inverse", this->inv), std::make_pair("pow", this->pow),
        std::make_pair("root", this->root)
    }))
{
    SETUP_UI;
    resultLabel = window->findChild<QLabel*>("resultLabel");
    interLabel = window->findChild<QLabel*>("intermediateLabel");
    auto allButtons = MainWindow->findChildren<QPushButton*>();
    foreach(QPushButton* button, allButtons){
        connect(button, SIGNAL(clicked()), this, SLOT(buttonPushed()));
    }
    this->getResult();
}

GeneralCalculator::~GeneralCalculator(){}

void GeneralCalculator::buttonPushed(){
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
            std::cout << "Map Operators does not have a key : " << funcName.toStdString() << "\n";
            std::cout << "in " << __FILE__ << " : " << __LINE__ << "\n";
            exit(1);
        }
    }
}

QString GeneralCalculator::getResult(const bool &chopDot){
    QString &&result = this->resultLabel->text();
    if(chopDot){
        if(result.back() == '.'){
            this->setResult(result.chopped(1));
        }
    }
    return result;
}

void GeneralCalculator::appendResult(const QString &str){
    this->setResult(this->getResult(false)+str);
}

void GeneralCalculator::prependResult(const QString &str){
    this->setResult(str + this->getResult(false));
}

void GeneralCalculator::chopResult(const int &num){
    this->setResult(this->getResult(false).chopped(num));
}

void GeneralCalculator::removeResult(const int &num){
    this->setResult(this->getResult(false).remove(0, num));
}

void GeneralCalculator::removeResult(const int &pos, const int &num){
    this->setResult(this->getResult(false).remove(pos, num));
}

void GeneralCalculator::setResult(const QString &str){
    this->resultLabel->setText(str);
}

QString GeneralCalculator::getInter() const{
    return this->interLabel->text();
}

void GeneralCalculator::appendInter(const QString &str, const bool &autoSpace){
    if(this->getInter().isEmpty())
        this->setInter(str);
    else{
        if(autoSpace)
            this->setInter(this->getInter() + " " + str);
        else
            this->setInter(this->getInter() + str);
    }
}

void GeneralCalculator::prependInter(const QString &str, const bool &autoSpace){
    if(this->getInter().isEmpty())
        this->setInter(str);
    else{
        if(autoSpace)
            this->setInter(str + " " + this->getInter());
        else
            this->setInter(str + this->getInter());
    }
}

void GeneralCalculator::chopInter(const int &num){
    this->setInter(this->getInter().chopped(num));
}

void GeneralCalculator::removeInter(const int &num){
    this->setResult(this->getInter().remove(0, num));
}

void GeneralCalculator::removeInter(const int &pos, const int &num){
    this->setResult(this->getInter().remove(pos, num));
}

QString GeneralCalculator::chopInterOp(const int &num){
    QString&& inter = this->getInter();
    int index;
    for(int i=0; i<num; ++i){
        if((index = inter.lastIndexOf(" ")) == -1)
            return "";
        inter.chop(inter.length() - index);
    }
    return inter;
}

QString GeneralCalculator::removeInterOp(const int &num){
    QString&& inter = this->getInter();
    int index;
    for(int i=0; i<num; ++i)
        if((index = inter.indexOf(" ")) == -1)
            return "";
        inter = inter.remove(0, inter.indexOf(" ") + 1);
    return inter;
}

void GeneralCalculator::setInter(const QString &str){
    this->interLabel->setText(str);
}

QString GeneralCalculator::lastOp() const{
    QString&& inter = this->getInter();
    int lastIndex;
    if((lastIndex = inter.lastIndexOf(" ")) == -1)
        return inter;
    else
        return inter.remove(0, lastIndex+1);
}

bool GeneralCalculator::isLastOpArithmetic() const{
    QString&& op = this->lastOp();
    return op == Operator::Normal::plus || op == Operator::Normal::minus || op == Operator::Normal::mult ||
           op == Operator::Normal::divide || op == Operator::Normal::altMult || op == Operator::Normal::altDivide;
}

void GeneralCalculator::replaceLastOp(const QString &str){
    QString&& expr = this->getInter();
    if(expr.lastIndexOf(" ") == -1)
        this->setInter(str);
    else
        this->setInter(expr.replace(expr.lastIndexOf(" ")+1, expr.length(), str));
}

bool GeneralCalculator::isBracketUnclosed() const{
    return this->getInter().count(Operator::Normal::leftBracket) > this->getInter().count(Operator::Normal::rightBracket);
}

bool GeneralCalculator::endsWithBracket() const{
    return this->getInter().endsWith(Operator::Normal::rightBracket);
}

void GeneralCalculator::closeAllBracket(){
    this->appendInter(this->getResult(), false);
    while(this->isBracketUnclosed())
        this->appendInter(Operator::Normal::rightBracket);
}

void GeneralCalculator::addNumber(const QString &str){
    if(this->calculated){
        if(!this->getInter().isEmpty() && !this->isLastOpArithmetic())
            this->setInter(this->chopInterOp(1));
        this->setResult(str);
        this->calculated = false;
    }
    else{
        if(this->getResult(false) == "0"){
            if(str == "0")
                return;
            else{
                this->setResult(str);
            }
        }
        else{
            if(this->specialStart){
                this->setResult(str);
                this->specialStart = false;
            }
            else
                this->appendResult(str);
        }
    }
}

void GeneralCalculator::calculate(){
    if(this->getInter().isEmpty())
        return;
    else{
        if(this->isBracketUnclosed()){
            this->closeAllBracket();
            this->setResult(calculateExpr(this->getInter()));
        }
        else{
            if(this->endsWithBracket())
                this->setResult(calculateExpr(this->getInter()));
            else
                this->setResult(calculateExpr(this->getInter() + " " + this->getResult()));
        }
    }
    this->setInter("");
    this->calculated = true;
}

void GeneralCalculator::calculate(const QString &op){
    QString &&result = this->getResult();
    if(this->getInter().isEmpty()) return;
    else{
        if(this->endsWithBracket()){
            this->setResult(calculateExpr(this->getInter()));
            this->appendInter(op);
        }
        else{
            this->setResult(calculateExpr(this->getInter() + " " + this->getResult()));
            this->appendInter(result);
            this->appendInter(op);
        }
    }
    this->calculated = true;
}

void GeneralCalculator::arithmetic(const QString &op){
    if(this->getInter().isEmpty()){
        this->setInter(this->getResult() + " " + op);
        this->calculated = true;
    }
    else if(this->calculated){
        if(this->lastOp() == op)
            return;
        else{
            if(this->isLastOpArithmetic())
                this->replaceLastOp(op);
            else
                this->appendInter(op);
        }
    }
    else{
        if(this->isLastOpArithmetic() || !this->specialStart)
            this->calculate(op);
        else{
            this->replaceLastOp(op);
            this->specialStart = false;
            this->calculated = true;
        }
    }
}
void GeneralCalculator::plus(){
    this->arithmetic(Operator::Normal::plus);
}

void GeneralCalculator::minus(){
    this->arithmetic(Operator::Normal::minus);
}

void GeneralCalculator::multiply(){
    this->arithmetic(Operator::Normal::mult);
}

void GeneralCalculator::divide(){
    this->arithmetic(Operator::Normal::divide);
}

void GeneralCalculator::equal(){
    this->calculate();
}

void GeneralCalculator::erase(){
    if(!this->getResult().isEmpty() && !this->calculated){
        this->chopResult(1);
    }
}

void GeneralCalculator::dot(){
    if(this->calculated)
        this->setResult("0.");
    else{
        if(this->getResult().indexOf(".") == -1)
            this->appendResult(".");
    }
}

void GeneralCalculator::negate(){
    QString &&result = this->getResult(false);
    if(result == "0") return;
    if(this->calculated)
        this->unarySpecial(Operator::Special::negate);
    else{
        if(result.front() == '-'){
            this->removeResult(1);
        }
        else
            this->prependResult("-");
    }
}

void GeneralCalculator::ce(){
    this->setResult("");
    this->calculated = false;
}

void GeneralCalculator::c(){
    this->setResult("");
    this->setInter("");
    this->calculated = false;
}

void GeneralCalculator::percent(){
    double result = calculateExpr(this->chopInterOp(1)).toDouble() * this->getResult().toDouble() / 100;
    QString &&str = QString::fromStdString(doubleToString(result));
    this->appendInter(str);
    this->setResult(str);
    this->calculated = true;
}

void GeneralCalculator::unarySpecial(const QString &op){
    if(this->getInter().isEmpty() || !this->calculated || this->isLastOpArithmetic()){
        QString &&expr = QString("%1(%2)").arg(op).arg(this->getResult());
        this->appendInter(expr);
        this->setResult(calculateExpr(expr));
        this->calculated = true;
    }
    else{
        QString &&expr = QString("%1(%2)").arg(op).arg(this->lastOp());
        this->replaceLastOp(expr);
        this->setResult(calculateExpr(expr));
    }
}

void GeneralCalculator::binarySpecial(const QString &op){
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

void GeneralCalculator::sqrt(){
    this->unarySpecial(Operator::Special::sqrt);
}

void GeneralCalculator::sqr(){
    this->unarySpecial(Operator::Special::sqr);
}

void GeneralCalculator::inv(){
    this->unarySpecial(Operator::Special::inv);
}

void GeneralCalculator::root(){
    this->binarySpecial(Operator::Special::root);
}

void GeneralCalculator::pow(){
    this->binarySpecial(Operator::Special::pow);
}

void GeneralCalculator::sin(){
    this->unarySpecial(Operator::Special::sin);
}

void GeneralCalculator::cos(){
    this->unarySpecial(Operator::Special::pow);
}

void GeneralCalculator::tan(){
    this->unarySpecial(Operator::Special::tan);
}

void GeneralCalculator::asin(){
    this->unarySpecial(Operator::Special::asin);
}

void GeneralCalculator::acos(){
    this->unarySpecial(Operator::Special::acos);
}

void GeneralCalculator::atan(){
    this->unarySpecial(Operator::Special::atan);
}

void GeneralCalculator::sinh(){
    this->unarySpecial(Operator::Special::sinh);
}

void GeneralCalculator::cosh(){
    this->unarySpecial(Operator::Special::cosh);
}

void GeneralCalculator::tanh(){
    this->unarySpecial(Operator::Special::tanh);
}

void GeneralCalculator::log(){
    this->unarySpecial(Operator::Special::log);
}

void GeneralCalculator::mod(){
    this->unarySpecial(Operator::Special::mod);
}

void GeneralCalculator::fac(){
    this->unarySpecial(Operator::Special::fac);
}
