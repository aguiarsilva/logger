#include "../include/logger/sink.hpp"
#include "../include/logger/formatter.hpp"

namespace logger {

   Sink::Sink(std::unique_ptr<Formatter> formatter) : _formatter(std::move(formatter)) {}
   
   Sink::~Sink() = default;
   
   std::string Sink::format(const LogMessage& msg) const
   {
        return _formatter->format(msg);
   }
}