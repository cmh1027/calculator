#include <stdexcept>
#include "exception.h"
namespace std{
    InvalidExprException::InvalidExprException() : std::runtime_error("Invalid expression"){}
}
