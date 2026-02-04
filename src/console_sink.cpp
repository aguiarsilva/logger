#include "../include/logger/console_sink.hpp"
#include <iostream>

namespace logger {
    ConsoleSink::ConsoleSink(std::unique_ptr<Formatter> formatter) : Sink(std::move(formatter)) {}

    void ConsoleSink::write(const LogMessage& msg) {
        std::cout << format(msg) << std::endl;
    }
}