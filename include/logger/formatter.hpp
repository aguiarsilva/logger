#pragma once

#include <string>
#include "sink.hpp"

namespace logger {

    class Formatter {
        public:
            virtual ~Formatter() = default;
            virtual std::string format(const LogMessage& msg) = 0;
    };

    class SimpleFormatter : public Formatter {
        public:
            std::string format(const LogMessage& msg) override;

    };

};