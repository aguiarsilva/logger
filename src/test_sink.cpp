#include "../include/logger/test_sink.hpp"
#include "../include/logger/sink.hpp"

TestSink::TestSink() : Sink(nullptr) {}

void TestSink::write(const logger::LogMessage& message){
    std::lock_guard<std::mutex> lock(mutex);
    messages.push_back(message);
}

const std::vector<logger::LogMessage>& TestSink::get_messages() const {
    return messages;
}