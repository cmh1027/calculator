#include "calculator.h"

const QMap<QString, void(*)(QStack<QString>& stack)> Operator::operateFuncs = {
    {"+", Operation::plus}, {"-", Operation::minus}, {"×", Operation::mult},
    {"÷", Operation::divide}, {"root", Operation::root}, {"pow", Operation::pow},
    {"inv", Operation::inv}, {"sin", Operation::sin}, {"cos", Operation::cos},
    {"tan", Operation::tan}, {"asin", Operation::asin}, {"acos", Operation::acos},
    {"atan", Operation::atan}, {"log", Operation::log}, {"mod", Operation::mod},
    {"fac", Operation::fac}, {"sinh", Operation::sinh}, {"cosh", Operation::cosh},
    {"tanh", Operation::tanh}, {"*", Operation::mult}, {"/", Operation::divide}
};

bool isOperand(const QString& expr){
    bool isDouble;
    expr.toDouble(&isDouble);
    return isDouble;
}

void processOp(QQueue<QString>&& ops, QStack<QString>& stack, QString& result){
    processOperator(ops.front(), stack, result);
    ops.pop_front();
    while(!ops.empty()){
        processOperand(ops.front(), result);
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
    else if(_operator == Operator::Normal::RightBracket){
        while(stack.top() != Operator::Normal::LeftBracket){
            result.append(stack.top());
            result.append(" ");
            stack.pop();
        }
        stack.pop();
    }
    else{
        while(!stack.empty() && precedence(stack.top()) >= precedence(_operator)){
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
    if(expr == "") return QString("0");
    while(chunking(expr, chunk, " ", start, end)){
        if(isOperand(chunk)){
            stack.push(chunk);
        }
        else{
            Operator::operateFuncs[chunk](stack);
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
    if(chunk == "")
        start = 0;
    end = nextIndex(expr, start, delimiter);
    if(end == -2)
        return false;
    else{
        chunk = expr.mid(start, end-start);
        start = end+1;
        return true;
    }
}

QString changeToPostfix(const QString& expr){
    int start = 0, end;
    QStack<QString> stack;
    QString chunk, result;
    if(expr == "") return "0";
    while(chunking(expr, chunk, " ", start, end)){
        if(isSpecialOperator(chunk)){;
            processOp(splitOperator(chunk), stack, result);
        }
        else{
            processOp(chunk, stack, result);
        }
    }
    remainOperators(stack, result);
    return result.trimmed();
}

int precedence(const QString& op){
    if(op == Operator::Normal::Plus) return 2;
    else if(op == Operator::Normal::Minus) return 2;
    else if(op == Operator::Normal::Mult) return 3;
    else if(op == Operator::Normal::Divide) return 3;
    else if(op == Operator::Normal::LeftBracket) return 1;
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


QQueue<QString> splitOperator(const QString& expr){
    int left, right;
    int start = 0, end;
    QQueue<QString> queue;
    QString chunk;
    if((left = expr.indexOf("(")) != -1 && (right = expr.indexOf(")")) != -1){
        queue.push_back(expr.mid(0, left));
        while(chunking(expr.mid(left+1, right-left-1), chunk, ",", start, end)){
            queue.push_back(chunk);
        }
    }
    return queue;
}
