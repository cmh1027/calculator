#include "calculator.h"

int nextIndex(const QString& expr, int start){
    int end = expr.indexOf(" ", start);
    if(end == -1){
        return expr.length();
    }
    else if(start == expr.length()+1){
        return -2;
    }
    else{
        return end;
    }
}
void processOp(const QPair<QString, QString>& ops, std::stack<QString>& stack, QString& result){
    processOperator(ops.first, stack, result);
    processOperand(ops.second, result);
}

void processOp(const QString& op, std::stack<QString>& stack, QString& result){
    bool isDouble;
    op.toDouble(&isDouble);
    if(isDouble){
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

void processOperator(const QString& _operator, std::stack<QString>& stack, QString& result){
    if(stack.empty()) stack.push(_operator);
    else{

    }
}

double calculate(const QString& expr){
    return calculatePostfix(changeToPostfix(expr));
}

QString changeToPostfix(const QString& expr){
    int start = 0, end;
    std::stack<QString> stack;
    QString chunk, result;
    if(expr == "") return "0";
    while((end = nextIndex(expr, start)) != -2){
        chunk = expr.mid(start, end-start);
        if(isSpecialOperator(chunk)){
            processOp(splitOperator(chunk), stack, result);
        }
        else{
            processOp(chunk, stack, result);
        }
        start = end+1;
    }
}

double calculatePostfix(const QString&& expr){

}

int precedence(const QString& op){
    if(op == "+") return 2;
    else if(op == "-") return 2;
    else if(op == "×") return 3;
    else if(op == "÷") return 3;
    else if(op == "(") return 1;
    else return 4;
}

bool isSpecialOperator(const QString& expr){
    if(expr.indexOf("(") != -1 && expr.indexOf(")") != -1){
        return true;
    }
    else{
        return false;
    }
}

QPair<QString, QString> splitOperator(const QString& expr){
    int left, right;
    if((left = expr.indexOf("(")) != -1 && (right = expr.indexOf(")")) != -1){
        return qMakePair(expr.mid(0, left), expr.mid(left+1, right-left-1));
    }
    else{
        return qMakePair("", 0);
    }
}