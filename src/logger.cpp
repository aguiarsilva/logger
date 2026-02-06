#include "../include/logger/logger.hpp"
#include "../include/logger/sink.hpp"
#include "../include/logger/log_messages.hpp"
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
        _level(LogLevel::Info),
        _running(true),
        _worker(&Logger::worker_loop, this) {}
    
    Logger::~Logger() {
        {
        std::lock_guard<std::mutex> lock(_queue_mutex);
        _running = false;
        }
        _cv.notify_one();

        if (_worker.joinable())
            _worker.join();
    }

     void Logger::set_level(LogLevel level)
     {
        std::lock_guard<std::mutex> lock(_queue_mutex);
        
        _level = level;
     }

     void    Logger::add_sink(std::shared_ptr<Sink> sink) {
        std::lock_guard<std::mutex> lock(_queue_mutex);

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

        {
            std::lock_guard<std::mutex> lock(_queue_mutex);
            _queue.push(std::move(message));
        }
        _cv.notify_one();
    }

     void    Logger::trace(const std::string& message) {
        log(LogLevel::Trace, message);
    }

    void    Logger::debug(const std::string& message) {
        log(LogLevel::Debug, message);
    }

    void    Logger::info(const std::string& message) {
        log(LogLevel::Info, message);
    }
    
    void    Logger::warn(const std::string& message) {
        log(LogLevel::Warn, message);
    }
    
    void    Logger::error(const std::string& message) {
        log(LogLevel::Error, message);
    }

    void    Logger::worker_loop() {
        while (true) {
            std::unique_lock<std::mutex> lock(_queue_mutex);

            _cv.wait(lock, [this] {
                return !_queue.empty() || !_running;
            });

            while (!_queue.empty()) {
                LogMessage msg = std::move(_queue.front());
                _queue.pop();

                lock.unlock();

                for (const auto& sink : _sinks) {
                    sink->write(msg);
                } 

                lock.lock();
            }

            if (!_running && _queue.empty())
                break;
        }

    }

}