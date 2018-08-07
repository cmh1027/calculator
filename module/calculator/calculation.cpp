#include <QtCore/QString>
#include "calculation.h"
#include "operator.h"
#include "constant.h"
#include "../../config/config.h"
#include "../exception.h"
extern Configuration* config;

namespace Calculation{
    bool isOperand(const QString& expr){
        bool isDouble;
        expr.toDouble(&isDouble);
        return isDouble || (expr.indexOf("{") != -1 && expr.indexOf("}") != -1);
    }

    void processOp(const QString& op, CStack<QString>& stack, QString& result){
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

    void processOperator(const QString& _operator, CStack<QString>& stack, QString& result){
        if(stack.empty()) stack.push(_operator);
        else if(_operator == Operator::Normal::rightBracket){
            while(stack.top() != Operator::Normal::leftBracket){
                result.append(stack.pop());
                result.append(" ");
            }
            stack.pop();
            while(!stack.empty() && precedence(stack.top()) > precedence(Operator::Normal::mult) &&
                  stack.top() != Operator::Normal::leftBracket){
                result.append(stack.pop());
                result.append(" ");
            }
        }
        else{
            if(_operator != Operator::Normal::leftBracket){
                while(!stack.empty() && precedence(stack.top()) >= precedence(_operator) &&
                      stack.top() != Operator::Normal::leftBracket){
                    result.append(stack.pop());
                    result.append(" ");
                }
            }
            stack.push(_operator);
        }
    }

    void remainOperators(CStack<QString>& stack, QString& result){
        while(!stack.empty()){
            result.append(stack.pop());
            result.append(" ");
        }
    }

    QString calculateExpr(QString& expr, CMap<QString, Const::ConstObject>& doubleList){
        QString &&result = "";
        try{
            result = calculatePostfix(changeToPostfix(expr), doubleList, expr);
        }
        catch(std::InvalidExprException &e){
            result = e.what();
        }
        return result;
    }

    QString changeToPostfix(const QString& expr){
        QString str = expr;
        str.replace(" ", "");
        int start = 0;
        CStack<QString> stack;
        QString chunk, result;
        if(str.isEmpty()) return "0";
        while(chunking(str, chunk, start)){
            processOp(chunk, stack, result);
        }
        remainOperators(stack, result);
        return result.trimmed();
    }

    QString calculatePostfix(const QString& expr, CMap<QString, Const::ConstObject>& doubleList, const QString& originalExpr){
        CStack<double> stack;
        if(expr.isEmpty()) return QString("0");
        foreach(const QString &chunk, expr.split(" ")){
            if(isOperand(chunk)){
                if(chunk.indexOf("{") != -1 && chunk.indexOf("}") != -1)
                    stack.push(doubleList.value(chunk));
                else
                    stack.push(chunk.toDouble());
            }
            else{
                if(!config->getRadian() && (chunk == Operator::Special::sin || chunk == Operator::Special::cos ||
                   chunk == Operator::Special::tan)){
                   double degree = stack.pop()*Const::PI/180;
                   stack.push(degree);
                }
                Operator::operateFuncs[chunk](stack);
            }
        }
        if(std::isnan(stack.top())){
            return "Invalid input";
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
                doubleList[format] = Const::ConstObject(stack.top(), originalExpr, false);
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

    void numberChunk(const QString& expr, QString& chunk, int& start){
        bool dotExist = false;
        int index;
        for(index = start; index < expr.length(); ++index){
            if(expr.at(index) == "."){
                if(dotExist){
                    throw std::InvalidExprException();
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
        throw std::InvalidExprException();
    }

    void specialChunk(const QString& expr, QString& chunk, int& start){
        for(int index = start; index < expr.length(); ++index){
            if(!(expr.at(index).isUpper() || expr.at(index).isLower())){
                chunk = expr.mid(start, index-start);
                start = index;
                return;
            }
        }
        throw std::InvalidExprException();
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
