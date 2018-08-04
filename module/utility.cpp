#include "utility.h"
#include "../config/config.h"
#include "exception.h"
#include <sstream>
#include <iomanip>

extern Configuration* config;

namespace Utility{
    QString doubleToString(const double &number){
        std::stringstream strs;
        int precision = config->getPrecision();
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

    QString transformExpr(const QString& str, CMap<QString, double>& list){
        int left, right;
        QString &&key = "";
        QString result = str;
        while((left = result.indexOf("{")) != -1 && (right = result.indexOf("}")) != -1){
            if(left == -1 || right == -1){
                throw std::InvalidExprException();
            }
            key = result.mid(left, right-left+1);
            result.replace(left, right-left+1, Utility::doubleToString(list[key]));
        }
        return result;
    }
}



