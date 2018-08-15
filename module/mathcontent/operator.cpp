#include <QString>
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
        {Operator::Normal::plus, Operation::OperationObject(Operation::plus, "Plus", Operation::Arithmetic)},
        {Operator::Normal::minus, Operation::OperationObject(Operation::minus, "Minus", Operation::Arithmetic)},
        {Operator::Normal::mult, Operation::OperationObject(Operation::mult, "Multiply", Operation::Arithmetic)},
        {Operator::Normal::divide, Operation::OperationObject(Operation::divide, "Divide", Operation::Arithmetic)},
        {Operator::Normal::altMult, Operation::OperationObject(Operation::mult, "Multiply", Operation::Arithmetic)},
        {Operator::Normal::altDivide, Operation::OperationObject(Operation::divide, "Divide", Operation::Arithmetic)},
        {Operator::Special::sqrt, Operation::OperationObject(Operation::sqrt, "Square root", Operation::Unary)},
        {Operator::Special::root, Operation::OperationObject(Operation::root, "Root", Operation::Binary)},
        {Operator::Special::sqr, Operation::OperationObject(Operation::sqr, "Square", Operation::Unary)},
        {Operator::Special::cube, Operation::OperationObject(Operation::cube, "Cube", Operation::Arithmetic)},
        {Operator::Special::pow, Operation::OperationObject(Operation::pow, "Power", Operation::Binary)},
        {Operator::Special::negate, Operation::OperationObject(Operation::negate, "Negate", Operation::Unary)},
        {Operator::Special::inv, Operation::OperationObject(Operation::inv, "Inverse", Operation::Unary)},
        {Operator::Special::sin, Operation::OperationObject(Operation::sin, "Sine", Operation::Unary)},
        {Operator::Special::cos, Operation::OperationObject(Operation::cos, "Cosine", Operation::Unary)},
        {Operator::Special::tan, Operation::OperationObject(Operation::tan, "Tangent", Operation::Unary)},
        {Operator::Special::asin, Operation::OperationObject(Operation::asin, "Arcsine", Operation::Unary)},
        {Operator::Special::acos, Operation::OperationObject(Operation::acos, "Arccosine", Operation::Unary)},
        {Operator::Special::atan, Operation::OperationObject(Operation::atan, "Arctangent", Operation::Unary)},
        {Operator::Special::log, Operation::OperationObject(Operation::log, "Logarithmic", Operation::Unary)},
        {Operator::Special::ln, Operation::OperationObject(Operation::ln, "Natural logarithmic", Operation::Unary)},
        {Operator::Special::mod, Operation::OperationObject(Operation::mod, "Mod", Operation::Binary)},
        {Operator::Special::abs, Operation::OperationObject(Operation::abs, "Absolute value", Operation::Unary)},
        {Operator::Special::fac, Operation::OperationObject(Operation::fac, "Factorial", Operation::Unary)},
        {Operator::Special::sinh, Operation::OperationObject(Operation::sinh, "Hyperbolic sine", Operation::Unary)},
        {Operator::Special::cosh, Operation::OperationObject(Operation::cosh, "Hyperbolic cosine", Operation::Unary)},
        {Operator::Special::tanh, Operation::OperationObject(Operation::tanh, "Hyperbolic tangent", Operation::Unary)}
    };
}

