#pragma once

#include <string>
#include "log_level.hpp"

namespace logger {
    //LogMessage structure should have all the content that the sink might need
    struct LogMessage {
        std::string logger_name;
        LogLevel    level;
        std::string timestamp;
        std::string text;
    };
};