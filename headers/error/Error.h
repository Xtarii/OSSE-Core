#ifndef OSSE_ERROR
#define OSSE_ERROR

#include <stdexcept>
#include <string>

namespace OSSE {
    /**
     * OSSE Exception
     */
    struct exception : std::logic_error {
        private:
            /**
             * Exception Message
             */
            const char* message_;

        public:
            /**
             * Construct a new exception object
             *
             * @param message Exception Message
             */
            exception(const char* message);

            /**
             * Error Message
             *
             * @return Message
             */
            const char* message() const;
    };
}

#endif // OSSE_ERROR
