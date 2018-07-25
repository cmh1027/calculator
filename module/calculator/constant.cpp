#include "constant.h"
QMap<QString, double> Const::Constant = {
    {"pi", M_PI}, {"e", M_E}
};

QString doubleToString(const double &number, const int &precision){
    std::ostringstream strs;
    if(precision >= 0)
        strs << std::fixed << std::setprecision(precision) << number;
    else
        strs << number;
    std::string str = strs.str();
    return QString::fromStdString(str);
}
