#include "../../headers/error/Error.h"
#include <stdexcept>

using namespace OSSE;

exception::exception(const char* message) : std::logic_error(message) {
    message_ = message;
}

const char* exception::message() const { return message_; }
