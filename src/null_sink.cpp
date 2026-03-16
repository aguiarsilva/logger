#include "../include/logger/null_sink.hpp" 
#include "../include/logger/formatter.hpp"

namespace logger {

    NullSink::NullSink([[maybe_unused]]std::unique_ptr<Formatter> formatter) :
        Sink(std::make_unique<SimpleFormatter>()) {}

    void NullSink::write([[maybe_unused]]const LogMessage& msg) {}
}
