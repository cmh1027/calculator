#include "operator.h"
namespace Operator{
    namespace Normal{
        const QString plus = "+";
        const QString minus = "-";
        const QString mult = "×";
        const QString divide = "÷";
        const QString leftBracket = "(";
        const QString rightBracket = ")";
        const QString altMult = "*";
        const QString altDivide = "/";
    }
    namespace Special{
        const QString sqrt = "sqrt";
        const QString sqr = "sqr";
        const QString cube = "cube";
        const QString root = "root";
        const QString pow = "pow";
        const QString inv = "inv";
        const QString sin = "sin";
        const QString cos = "cos";
        const QString tan = "tan";
        const QString asin = "asin";
        const QString acos = "acos";
        const QString atan = "atan";
        const QString log = "log";
        const QString ln = "ln";
        const QString mod = "mod";
        const QString fac = "fac";
        const QString sinh = "sinh";
        const QString cosh = "cosh";
        const QString tanh = "tanh";
        const QString negate = "negate";
        const QString abs = "abs";
    }

    CMap<QString, Operation::OperationObject> operateFuncs = {
        {Operator::Normal::plus, Operation::OperationObject(Operation::plus, "Plus")},
        {Operator::Normal::minus, Operation::OperationObject(Operation::minus, "Minus")},
        {Operator::Normal::mult, Operation::OperationObject(Operation::mult, "Multiply")},
        {Operator::Normal::divide, Operation::OperationObject(Operation::divide, "Divide")},
        {Operator::Normal::altMult, Operation::OperationObject(Operation::mult, "Multiply")},
        {Operator::Normal::altDivide, Operation::OperationObject(Operation::divide, "plus")},
        {Operator::Special::sqrt, Operation::OperationObject(Operation::sqrt, "Square root")},
        {Operator::Special::root, Operation::OperationObject(Operation::root, "Root")},
        {Operator::Special::sqr, Operation::OperationObject(Operation::sqr, "Square")},
        {Operator::Special::cube, Operation::OperationObject(Operation::cube, "Cube")},
        {Operator::Special::pow, Operation::OperationObject(Operation::pow, "Power")},
        {Operator::Special::negate, Operation::OperationObject(Operation::negate, "Negate")},
        {Operator::Special::inv, Operation::OperationObject(Operation::inv, "Inverse")},
        {Operator::Special::sin, Operation::OperationObject(Operation::sin, "Sine")},
        {Operator::Special::cos, Operation::OperationObject(Operation::cos, "Cosine")},
        {Operator::Special::tan, Operation::OperationObject(Operation::tan, "Tangent")},
        {Operator::Special::asin, Operation::OperationObject(Operation::asin, "Arcsine")},
        {Operator::Special::acos, Operation::OperationObject(Operation::acos, "Arccosine")},
        {Operator::Special::atan, Operation::OperationObject(Operation::atan, "Arctangent")},
        {Operator::Special::log, Operation::OperationObject(Operation::log, "Logarithmic")},
        {Operator::Special::ln, Operation::OperationObject(Operation::ln, "Natural logarithmic")},
        {Operator::Special::mod, Operation::OperationObject(Operation::mod, "Mod")},
        {Operator::Special::abs, Operation::OperationObject(Operation::abs, "Absolute value")},
        {Operator::Special::fac, Operation::OperationObject(Operation::fac, "Factorial")},
        {Operator::Special::sinh, Operation::OperationObject(Operation::sinh, "Hyperbolic sine")},
        {Operator::Special::cosh, Operation::OperationObject(Operation::cosh, "Hyperbolic cosine")},
        {Operator::Special::tanh, Operation::OperationObject(Operation::tanh, "Hyperbolic tangent")},
    };
}
