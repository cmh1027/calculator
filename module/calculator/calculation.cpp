#include "calculation.h"

bool isOperand(const QString& expr){
    bool isDouble;
    expr.toDouble(&isDouble);
    return isDouble;
}

void processOp(QQueue<QString>&& ops, QString& result){
    while(!ops.empty()){
        result.append(ops.front());
        result.append(" ");
        ops.pop_front();
    }
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
    }
    else{
        while(!stack.empty() && precedence(stack.top()) >= precedence(_operator) && _operator != "("){
            result.append(stack.top());
            result.append(" ");
            stack.pop();
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

QString calculateExpr(const QString& expr){
    QString result = calculatePostfix(changeToPostfix(expr));
    return result;
}

int nextIndex(const QString& expr, int start, const QString& delimiter){
    int end = expr.indexOf(delimiter, start);
    if(start == expr.length()+1){
        return -2;
    }
    else if(end == -1){
        return expr.length();
    }
    else{
        return end;
    }
}

QString calculatePostfix(const QString& expr){
    int start = 0, end;
    QStack<QString> stack;
    QString chunk;
    if(expr.isEmpty()) return QString("0");
    while(chunking(expr, chunk, " ", start, end)){
        if(isOperand(chunk)){
            stack.push(chunk);
        }
        else{
            if(Operator::operateFuncs.contains(chunk))
                Operator::operateFuncs[chunk](stack);
            else{
                std::cout << "Map operateFuncs does not have a key : " << chunk.toStdString() << "\n";
                std::cout << "in " << __FILE__ << " : " << __LINE__ << "\n";
                std::cout << "Expression : " << expr.toStdString() << "\n";
                exit(1);
            }
        }
    }
    if(stack.top() == "nan"){
        return QString("Invalid input");
    }
    else{
        return stack.top();
    }
}

bool chunking(const QString& expr, QString& chunk, const QString& delimiter, int& start, int& end){
    if(chunk.isEmpty())
        start = 0;
    end = nextIndex(expr, start, delimiter);
    if(end == -2)
        return false;
    else{
        chunk = expr.mid(start, end-start);
        if(chunk.isEmpty()){
            std::cout << "Chunk is empty!\n";
            std::cout << "Expression : " << expr.toStdString() << "\n";
            exit(1);
        }
        start = end+1;
        return true;
    }
}

QString changeToPostfix(const QString& expr){
    int start = 0, end;
    QStack<QString> stack;
    QString chunk, result;
    if(expr.isEmpty()) return "0";
    while(chunking(expr, chunk, " ", start, end)){
        if(isUnarySpecial(chunk)){;
            processOp(splitOperator(chunk), result);
        }
        else{
            processOp(chunk, stack, result);
        }
    }
    remainOperators(stack, result);
    return result.trimmed();
}

int precedence(const QString& op){
    if(op == Operator::Normal::plus) return 2;
    else if(op == Operator::Normal::minus) return 2;
    else if(op == Operator::Normal::mult) return 3;
    else if(op == Operator::Normal::divide) return 3;
    else if(op == Operator::Normal::leftBracket) return 1;
    else return 4;
}

bool isUnarySpecial(const QString& expr){
    if(expr.indexOf(Operator::Normal::leftBracket) != -1 && expr.indexOf(Operator::Normal::rightBracket) != -1){
        return true;
    }
    else{
        return false;
    }
}


QQueue<QString> splitOperator(const QString& expr){
    int start = 0;
    QQueue<QString> queue;
    QQueue<QString> stack;
    QString chunk;
    for(int index=0; index<expr.length(); index++){
        if(expr.at(index) == Operator::Normal::leftBracket){
            stack.push_back(expr.mid(start, index-start));
            start = index+1;
        }
        else if(expr.at(index) == Operator::Normal::rightBracket){
            if(start < index)
                queue.push_back(expr.mid(start, index-start));
            queue.push_back(stack.back());
            stack.pop_back();
            start = index + 1;
        }
    }
    return queue;
}