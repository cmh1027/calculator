#include "utility.h"
QString doubleToString(const double &number, int precision){
    std::stringstream strs;
    if(number - static_cast<long long int>(number)> 0 && precision >= 0){
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
