#include "../include/logger/logger.hpp"
#include "../include/logger/log_message.hpp"
#include <chrono>
#include <iomanip>
#include <ctime>
#include <sstream>

namespace logger {
    static  std::string timestamp_now(){
        auto now = std::chrono::system_clock::now();
        auto t = std::chrono::system_clock::to_time_t(now);

        std::ostringstream oss;
        oss << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

    //implement logger constructor
    Logger::Logger(const std::string& name) 
        : _name(name),
        _level(LogLevel::Info) {}

     void Logger::set_level(LogLevel level)
     {
        _level = level;
     }

     void    Logger::add_sink(std::shared_ptr<Sink> sink) {
        _sinks.push_back(std::move(sink));
     }

    void    Logger::log(LogLevel level, const std::string& msg) {
        if (_level < level)
            return;

        LogMessage message {
            _name,
            level,
            timestamp_now(),
            msg
        };

        for (const auto& sink : _sinks)
        {
            sink->write(message);
        }
    }

     void    Logger::trace(const std::string& message) {
        log(LogLevel::Trace, message);
    }

    void    debug(const std::string& message) {
        log(LogLevel::Debug, message);
    }

    void    Logger::info(const std::string& message) {
        log(LogLevel::Info, message);
    }
    
    void    LogLevel::warn(const std::string& message) {
        log(LogLevel::Warn, message);
    }
    
    void    LogLevel::error(const std::string& message) {
        log(LogLevel::Error, message);
    }

}