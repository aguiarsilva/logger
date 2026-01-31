#pragma once

#include <string>
#include "log_messages.hpp"

namespace logger {
    //Sink class should be an abstract class
    class Sink {
        public:
            virtual ~Sink() = default;
            virtual void write(const LogMessage& msg) = 0;
    };

};