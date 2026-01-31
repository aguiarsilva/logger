#pragma once

#include "logger/logger.hpp"
#include "logger/sink.hpp"
#include <memory>
#include <iostream>

int main() {
    auto console_sink = std::make_shared<logger::Sink>(); //Replace with actual ConsoleSink after it is done.
    logger::Logger log("MyApp");
    log.add_sink(console_sink);

    log.info("System started");
    log.warn("Low Memory");
    log.error("Something went wrong");

    return 0;

}