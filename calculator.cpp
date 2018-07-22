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
    //  pow(sqr(2),4) * 6
    //
    // 2 sqr 4 pow 6 *

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
    // pow(pow(2,2),2)
    // 2 2 pow 2 pow
    while(chunking(expr, chunk, " ", start, end)){
        if(isSpecialOperator(chunk)){;
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
    if(op == Operator::Normal::Plus) return 2;
    else if(op == Operator::Normal::Minus) return 2;
    else if(op == Operator::Normal::Mult) return 3;
    else if(op == Operator::Normal::Divide) return 3;
    else if(op == Operator::Normal::LeftBracket) return 1;
    else{
        std::cout << "Unknown operator " << op.toStdString() << "\n";
        exit(1);
    }
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
    int start = 0;
    QQueue<QString> queue;
    QQueue<QString> stack;
    QString chunk;
    for(int index=0; index<expr.length(); index++){
        if(expr.at(index) == '('){
            stack.push_back(expr.mid(start, index-start));
            start = index+1;
        }
        else if(expr.at(index) == ')'){
            if(start < index)
                queue.push_back(expr.mid(start, index-start));
            queue.push_back(stack.back());
            stack.pop_back();
            start = index + 1;
        }
        else if((expr.at(index) == ',')){
            if(start < index)
                queue.push_back(expr.mid(start, index-start));
            start = index + 1;
        }
    }

    // sqr(sqr(sqr(2)))
    // 2 sqr sqr sqr

    // pow(2,pow(pow(2,2),2))
    // 2 2 2 pow 2 pow pow



    return queue;
}
