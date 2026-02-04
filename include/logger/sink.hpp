#pragma once

#include <memory>
#include "log_messages.hpp"

namespace logger {
    //call the formatter class
    class Formatter;

    //Sink class should be an abstract class
    class Sink {
        public:
            explicit Sink(std::unique_ptr<Formatter> formatter);

            virtual ~Sink() = default;
            virtual void write(const LogMessage& msg) = 0;

        protected:
            std::string format(const LogMessage& msg) const;

        private:
            std::unique_ptr<Formatter> _formatter;
    };

}