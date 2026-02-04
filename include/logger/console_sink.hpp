#pragma once

#include "sink.hpp"
#include <iostream>

namespace logger {

    class ConsoleSink : public Sink {
        public:
            explicit ConsoleSink(std::unique_ptr<Formatter> formatter);

            void write(const LogMessage& msg) override;

    };

}