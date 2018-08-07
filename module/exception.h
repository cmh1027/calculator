#ifndef EXCEPTION_H
#define EXCEPTION_H
namespace std{
    class runtime_error;
}
namespace std{
    class InvalidExprException : public std::runtime_error{
    public:
        InvalidExprException();
        virtual ~InvalidExprException() = default;
    };
}
#endif // EXCEPTION_H
