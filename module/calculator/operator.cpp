#include "operator.h"
const QMap<QString, void(*)(QStack<QString>& stack)> Operator::operateFuncs = {
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
    {Operator::Special::cosh, Operation::cosh}, {Operator::Special::tanh, Operation::tanh}
};
