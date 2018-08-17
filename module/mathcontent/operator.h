#ifndef OPERATOR_H
#define OPERATOR_H
#include "../ctl.h"
#include "operation.h"
class QString;
namespace Operator{
    namespace Normal{
        extern const QString plus;
        extern const QString minus;
        extern const QString mult;
        extern const QString divide;
        extern const QString leftBracket;
        extern const QString rightBracket;
        extern const QString altMult;
        extern const QString altDivide;
    }
    namespace Special{
        extern const QString sqrt;
        extern const QString sqr;
        extern const QString cube;
        extern const QString root;
        extern const QString pow;
        extern const QString inv;
        extern const QString sin;
        extern const QString cos;
        extern const QString tan;
        extern const QString asin;
        extern const QString acos;
        extern const QString atan;
        extern const QString log;
        extern const QString ln;
        extern const QString mod;
        extern const QString fac;
        extern const QString sinh;
        extern const QString cosh;
        extern const QString tanh;
        extern const QString negate;
        extern const QString abs;
    }
}
#endif // OPERATOR_H
