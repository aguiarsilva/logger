#pragma once

#include "logger/logger.hpp"
#include "logger/sink.hpp"
#include "logger/console_sink.hpp"
#include "logger/file_sink.hpp"
#include "logger/simple_formatter.hpp"
#include <memory>
#include <iostream>

using namespace logger;

int main() {
  
    Logger log("MyApp");
    log.add_sink(std::make_shared<ConsoleSink> (
        std::make_unique<SimpleFormatter>()
    ));

    log.add_sink(std::make_shared<FileSink> (
        "app.log",
        std::make_unique<SimpleFormatter>()
    ));

    log.info("System started");
    log.warn("Low Memory");
    log.error("Something went wrong");

    return 0;

}