#ifndef CONSTANT_H
#define CONSTANT_H
#include "dataobject.h"
#include "../ctl.h"
class QString;
namespace Const{
    class ConstObject : public DataObject{
    private:
        double value;
        QString expression;

    public:
        ConstObject() = default;
        virtual ~ConstObject() = default;
        ConstObject(const double&, const bool& = false, const bool& = true, const QString& = "Temporary");
        operator double() const;
        double getValue() const;
        void setValue(const double&);
        QString getExpr() const;
        void setExpr(const QString&);
        void setExpr(const QString&, CMap<QString, Const::ConstObject*>&);
        bool update(CMap<QString, Const::ConstObject*>&);
    };

    extern const double PI;
    extern const double E;
}



#endif // CONSTANT_H
