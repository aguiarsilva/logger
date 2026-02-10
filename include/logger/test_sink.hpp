#pragma once

#include "sink.hpp"
#include <vector>
#include "log_messages.hpp"
#include <mutex>

class TestSink : public logger::Sink {
    public:
        TestSink();

        void write(const logger::LogMessage& message) override;
        const std::vector<logger::LogMessage>& get_messages() const;

    private:
        mutable std::mutex mutex;
        std::vector<logger::LogMessage> messages;
};