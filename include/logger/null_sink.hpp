#pragma once

#include <fstream>
#include "sink.hpp"

namespace logger {
    class NullSink : public Sink {
        public:
            NullSink(std::unique_ptr<Formatter> formatter);

            void write(const LogMessage& msg) override;
    };
}