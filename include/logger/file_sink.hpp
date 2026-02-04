#pragma once

#include <fstream>
#include "sink.hpp"

namespace logger {
    class FileSink : public Sink {
        public:
            FileSink(const std::string& filename, std::unique_ptr<Formatter> formatter);

            void write(const LogMessage& msg) override;

        private:
            std::ofstream _file;

    };
}