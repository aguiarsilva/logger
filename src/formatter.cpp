#include "logger/formatter.hpp"

namespace logger {

    static const char* level_to_str(LogLevel level)
    {
        switch (level)
        {
            case LogLevel::Debug: return "DEBUG";
            case LogLevel::Trace: return "TRACE";
            case LogLevel::Error: return "ERROR";
            case LogLevel::Info: return "INFO";
            case LogLevel::Warn: return "WARN";
        }
        return "UNKNOWN";
    }

    std::string SimpleFormatter::format(const LogMessage& msg) {
        return "[" + msg.timestamp + "]" 
            + "[" + level_to_str(msg.level) + "]" 
            + msg.text; 
    }
};