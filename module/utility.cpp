#include "utility.h"
#include "../config/config.h"
#include <sstream>
#include <iomanip>
#include <iostream>

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

    QString transformExpr(QString str, QMap<QString, double>& list){
        int left, right;
        QString &&key = "";
        while((left = str.indexOf("{")) != -1 && (right = str.indexOf("}")) != -1){
            if(left == -1 || right == -1){
                std::cout << "Something goes wrong\n";
                std::cout << str.toStdString() << "\n";
                std::cout << "in " << __FILE__ << " : " << __LINE__ << "\n";
                exit(1);
            }
            key = str.mid(left, right-left+1);
            if(list.contains(key)){
                str.replace(left, right-left+1, Utility::doubleToString(list[key]));
            }
            else{
                std::cout << "Repeating constant list does not have a key : " << key.toStdString() << "\n";
                std::cout << "in " << __FILE__ << " : " << __LINE__ << "\n";
                exit(1);
            }
        }
        return str;
    }
}



