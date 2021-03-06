#ifndef OPERATION_H
#define OPERATION_H
#include <QString>
#include "../ctl.h"
#include "dataobject.h"
#include "constant.h"

namespace Operation{
    namespace Unknown{
        extern const QString X;
        extern const QString Y;
    }

    enum Arity{Arithmetic, Unary, Binary};

    class OperationObject : public DataObject{
    private:
        using funcType = void(*)(CStack<double>&);
        funcType func;
        QString expression;
        Arity type;

    public:
        OperationObject() = default;
        virtual ~OperationObject() = default;
        OperationObject(const funcType&, const QString&, const Arity&, const bool& = false);
        OperationObject(const QString&, const QString&, const Arity&, const bool& = false);
        void operator()(CStack<double>&, CMap<QString, Const::ConstObject*>&);
        void call(CStack<double>&, CMap<QString, Const::ConstObject*>&);
        void setExpr(const QString&);
        QString getExpr() const;
        void setArity(Arity);
        Arity getArity() const;
        QString getArityString() const;
        QString funcShape(const QString&) const;
    };

    void plus(CStack<double>& stack);
    void minus(CStack<double>& stack);
    void mult(CStack<double>& stack);
    void divide(CStack<double>& stack);
    void sqrt(CStack<double>& stack);
    void root(CStack<double>& stack);
    void sqr(CStack<double>& stack);
    void cube(CStack<double>& stack);
    void pow(CStack<double>& stack);
    void inv(CStack<double>& stack);
    void negate(CStack<double>& stack);
    void sin(CStack<double>& stack);
    void cos(CStack<double>& stack);
    void tan(CStack<double>& stack);
    void asin(CStack<double>& stack);
    void acos(CStack<double>& stack);
    void atan(CStack<double>& stack);
    void sinh(CStack<double>& stack);
    void cosh(CStack<double>& stack);
    void tanh(CStack<double>& stack);
    void log(CStack<double>& stack);
    void ln(CStack<double>& stack);
    void mod(CStack<double>& stack);
    void fac(CStack<double>& stack);
    void abs(CStack<double>& stack);
}
#endif // OPERATION_H
