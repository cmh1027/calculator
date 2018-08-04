#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <stdexcept>
namespace std{
    class InvalidExprException : public std::runtime_error{
    public:
        InvalidExprException();
    };
}
#endif // EXCEPTION_H
