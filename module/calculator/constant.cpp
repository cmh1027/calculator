#include "constant.h"
#include <iostream>
QMap<QString, double> Const::Constant = {
    {"pi", M_PI}, {"e", M_E}
};

/*
void round(double &number, const int &precision){
    number *= std::pow(10, precision);
    if(number - static_cast<int>(number) >= 0.5)
        number+=1;
    number = static_cast<int>(number);
    number /= std::pow(10, precision);
}
*/

QString doubleToString(const double &number, int precision){
    std::stringstream strs;
    if(number - static_cast<int>(number)> 0){
        for(int point = 1; point<precision; ++point){
            if(number*std::pow(10, point) - std::floor(number*std::pow(10, point)) == 0){
                precision = point;
            }
        }
        strs << std::fixed << std::setprecision(precision) << number;
    }
    else
        strs << number;
    std::string str = strs.str();
    return QString::fromStdString(str);
}
