#ifndef CONSTANT_H
#define CONSTANT_H
#include "dataobject.h"
class QString;
namespace Const{
    class ConstObject : public DataObject{
    private:
        double value;

    public:
        ConstObject() = default;
        virtual ~ConstObject() = default;
        ConstObject(const double&, const QString& = "Temporary", const bool& = true);
        operator double() const;
    };

    extern const double PI;
    extern const double E;
}



#endif // CONSTANT_H
