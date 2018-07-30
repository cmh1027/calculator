#include "calculation.h"
#include "operator.h"
#include "constant.h"
#include "../../config/config.h"
#include "iostream"

extern Configuration* config;

namespace Calculation{
    bool isOperand(const QString& expr){
        bool isDouble;
        expr.toDouble(&isDouble);
        return isDouble || (expr.indexOf("{") != -1 && expr.indexOf("}") != -1);
    }

    void processOp(const QString& op, QStack<QString>& stack, QString& result){
        if(isOperand(op)){
            processOperand(op, result);
        }
        else{
            processOperator(op, stack, result);
        }
    }

    void processOperand(const QString& operand, QString& result){
        result.append(operand);
        result.append(" ");
    }

    void processOperator(const QString& _operator, QStack<QString>& stack, QString& result){
        if(stack.empty()) stack.push(_operator);
        else if(_operator == Operator::Normal::rightBracket){
            while(stack.top() != Operator::Normal::leftBracket){
                result.append(stack.top());
                result.append(" ");
                stack.pop();
            }
            stack.pop();
            while(!stack.empty() && precedence(stack.top()) > precedence(Operator::Normal::mult)){
                result.append(stack.top());
                result.append(" ");
                stack.pop();
            }
        }

        else{
            if(_operator != Operator::Normal::leftBracket){
                while(!stack.empty() && precedence(stack.top()) >= precedence(_operator)){
                    result.append(stack.top());
                    result.append(" ");
                    stack.pop();
                }
            }
            stack.push(_operator);
        }
    }

    void remainOperators(QStack<QString>& stack, QString& result){
        while(!stack.empty()){
            result.append(stack.top());
            result.append(" ");
            stack.pop();
        }
    }

    QString calculateExpr(QString& expr, QMap<QString, double>& doubleList){
        QString result = calculatePostfix(changeToPostfix(expr.replace(" ", "")), doubleList);
        return result;
    }


    QString calculatePostfix(const QString& expr, QMap<QString, double>& doubleList){
        QStack<double> stack;
        if(expr.isEmpty()) return QString("0");
        foreach(const QString &chunk, expr.split(" ")){
            if(isOperand(chunk)){
                if(chunk.indexOf("{") != -1 && chunk.indexOf("}") != -1)
                    stack.push(doubleList[chunk]);
                else
                    stack.push(chunk.toDouble());
            }
            else{
                if(Operator::operateFuncs.contains(chunk)){
                    if(!config->getRadian() && (chunk == Operator::Special::sin || chunk == Operator::Special::cos ||
                       chunk == Operator::Special::tan)){
                       double degree = stack.top()*Const::PI/180;
                       stack.pop();
                       stack.push(degree);
                    }
                    Operator::operateFuncs[chunk](stack);
                }
                else{
                    std::cout << "Map operateFuncs does not have a key : " << chunk.toStdString() << "\n";
                    std::cout << "in " << __FILE__ << " : " << __LINE__ << "\n";
                    std::cout << "Expression : " << expr.toStdString() << "\n";
                    exit(1);
                }
            }
        }
        if(std::isnan(stack.top())){
            return QString("Invalid input");
        }
        else{
            if(isInt(stack.top())){
                return QString::number(static_cast<long>(stack.top()));
            }
            else{
                for(auto it = doubleList.begin(); it != doubleList.end(); it++){
                    if(stack.top() == it.value())
                        return it.key();
                }
                QString format = QString("{%1}").arg(doubleList.size());
                doubleList[format] = stack.top();
                return format;
            }
        }
    }

    bool chunking(const QString& expr, QString& chunk, int& start){
        if(chunk.isEmpty())
            start = 0;
        if(start >= expr.length())
            return false;
        QChar firstChar = expr.at(start);
        if(firstChar.isDigit())
            numberChunk(expr, chunk, start);
        else if(firstChar == "{")
            symbolChunk(expr, chunk, start);
        else if(firstChar == Operator::Normal::leftBracket || firstChar == Operator::Normal::rightBracket ||
                isArithmetic(firstChar)){
            chunk = firstChar;
            start += 1;
        }
        else
            specialChunk(expr, chunk, start);
        return true;
    }

    // cos(sin(8*2)root3)
    // stack : cos ( sin
    // result : 8 2 *
    void numberChunk(const QString& expr, QString& chunk, int& start){
        bool dotExist = false;
        int index;
        for(index = start; index < expr.length(); ++index){
            if(expr.at(index) == "."){
                if(dotExist){
                    std::cout << "Invalid expression\n";
                    std::cout << expr.toStdString() << std::endl;
                    exit(1);
                }
                else{
                    dotExist = true;
                }
            }
            else{
                if(!expr.at(index).isDigit()){
                    chunk = expr.mid(start, index-start);
                    start = index;
                    return;
                }
            }
        }
        chunk = expr.mid(start, index-start+1);
        start = index+1;
    }

    void symbolChunk(const QString& expr, QString& chunk, int& start){
        for(int index = start; index < expr.length(); ++index){
            if(expr.at(index) == "}"){
                chunk = expr.mid(start, index-start+1);
                start = index + 1;
                return;
            }
        }
        std::cout << "Invalid expression\n";
        std::cout << expr.toStdString() << std::endl;
        exit(1);
    }

    void specialChunk(const QString& expr, QString& chunk, int& start){
        for(int index = start; index < expr.length(); ++index){
            if(!(expr.at(index).isUpper() || expr.at(index).isLower())){
                chunk = expr.mid(start, index-start);
                start = index;
                return;
            }
        }
        std::cout << "Invalid expression\n";
        std::cout << expr.toStdString() << std::endl;
        exit(1);
    }

    QString changeToPostfix(const QString& expr){
        int start = 0;
        QStack<QString> stack;
        QString chunk, result;
        if(expr.isEmpty()) return "0";
        while(chunking(expr, chunk, start)){
            processOp(chunk, stack, result);
        }
        remainOperators(stack, result);
        return result.trimmed();
    }

    int precedence(const QString& op){
        if(op == Operator::Normal::plus) return 1;
        else if(op == Operator::Normal::minus) return 1;
        else if(op == Operator::Normal::mult) return 2;
        else if(op == Operator::Normal::divide) return 2;
        else return 3;
    }

    bool isInt(const double& num){
        if(num - static_cast<long long int>(num) > 0)
            return false;
        else
            return true;
    }

    bool isArithmetic(const QString& op){
        return op == Operator::Normal::plus || op == Operator::Normal::minus || op == Operator::Normal::mult ||
               op == Operator::Normal::divide || op == Operator::Normal::altMult || op == Operator::Normal::altDivide;
    }
}
