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
    const QMap<QString, void(*)(QStack<double>& stack)> operateFuncs = {
        {Operator::Normal::plus, Operation::plus}, {Operator::Normal::minus, Operation::minus},
        {Operator::Normal::mult, Operation::mult}, {Operator::Normal::divide, Operation::divide},
        {Operator::Normal::altMult, Operation::mult}, {Operator::Normal::altDivide, Operation::divide},
        {Operator::Special::sqrt, Operation::sqrt}, {Operator::Special::root, Operation::root},
        {Operator::Special::sqr, Operation::sqr}, {Operator::Special::pow, Operation::pow},
        {Operator::Special::negate, Operation::negate}, {Operator::Special::inv, Operation::inv},
        {Operator::Special::sin, Operation::sin}, {Operator::Special::cos, Operation::cos},
        {Operator::Special::tan, Operation::tan}, {Operator::Special::asin, Operation::asin},
        {Operator::Special::acos, Operation::acos}, {Operator::Special::atan, Operation::atan},
        {Operator::Special::log, Operation::log}, {Operator::Special::ln, Operation::ln},
        {Operator::Special::mod, Operation::mod}, {Operator::Special::abs, Operation::abs},
        {Operator::Special::fac, Operation::fac}, {Operator::Special::sinh, Operation::sinh},
        {Operator::Special::cosh, Operation::cosh}, {Operator::Special::tanh, Operation::tanh},
        {Operator::Special::cube, Operation::cube}
    };
}
