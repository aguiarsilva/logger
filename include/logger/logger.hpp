#pragma once

#include <string>
#include <vector>
#include <memory>
#include "log_level.hpp"
#include "log_messages.hpp"
#include <mutex>
#include <queue>
#include <thread>
#include <condition_variable>
#include <atomic>

namespace logger {

    //Foward Declaration for class Sink
    class Sink;

    class Logger {
        public:
            explicit Logger(const std::string& name);

            //Prevent copy, allow to move
            Logger(const Logger&) = delete;
            Logger& operator=(const Logger&) = delete;
            Logger(Logger&&) noexcept = default;
            Logger& operator=(Logger&&) noexcept = default;
            //Destructor
            ~Logger();

            //set minimum log level
            void set_level(LogLevel level);

            //Logging functions
            void    trace(const std::string& message);
            void    debug(const std::string& message);
            void    info(const std::string& message);
            void    warn(const std::string& message);
            void    error(const std::string& message);

            //add a sink (console, file..., )
            void    add_sink(std::shared_ptr<Sink> sink);

        private:
            std::string _name;
            LogLevel    _level;
            std::vector<std::shared_ptr<Sink>> _sinks;

            std::mutex _queue_mutex;
            std::condition_variable _cv;
            std::queue<LogMessage> _queue;
            std::atomic<bool> _running;
            std::thread _worker;


            void    worker_loop();
            void    log(LogLevel level, const std::string& msg);
    };
}
