#include "../include/logger/file_sink.hpp"

namespace logger {
    FileSink::FileSink(const std::string& filename, std::unique_ptr<Formatter> formatter) : Sink(std::move(formatter)), _file(filename, std::ios::app) {}

    void FileSink::write(const LogMessage& msg) {
        if(_file.is_open())
            _file << format(msg) << std::endl;
    }
}
