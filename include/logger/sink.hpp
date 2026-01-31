#pragma once

#include <string>

namespace logger {

    //LogMessage structure should have all the content that the sink might need
    struct LogMessage {
        std::string text;
        std::string logger_name;
        LogLevel    level;
        std::string timestamp;
    };

    //Sink class should be an abstract class
    class Sink {
        public:
            virtual ~Sink() = default;
            virtual void write(const LogMessage& msg) = 0;
    };

};