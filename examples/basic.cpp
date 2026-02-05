#include "logger/logger.hpp"
#include "logger/sink.hpp"
#include "logger/console_sink.hpp"
#include "logger/file_sink.hpp"
#include "logger/formatter.hpp"
#include <memory>
#include <iostream>
#include <thread>
#include <vector>

using namespace logger;

static void basic_test(Logger& log) {
    log.info("System started");
    log.warn("Low memory");
    log.error("Something went wrong");
}

static void threaded_test(Logger& log) {
    const int thread_count = 4;
    const int messages_per_thread = 5;

    std::vector<std::thread> threads;

    for (int i = 0; i < thread_count; ++i) {
        threads.emplace_back([&log, i]() {
            for (int j = 0; j < messages_per_thread; ++j) {
                log.info("Thread " + std::to_string(i)
                    + " message " + std::to_string(j));
            }
        });
    }
    for (auto& t : threads) {
        t.join();
    }
}

int main() {
  
    Logger log("MyApp");
    log.add_sink(std::make_shared<ConsoleSink> (
        std::make_unique<SimpleFormatter>()
    ));

    log.add_sink(std::make_shared<FileSink> (
        "app.log",
        std::make_unique<SimpleFormatter>()
    ));

    //Single thread tests
    log.info("== BASIC LOGGING TEST ===");
    threaded_test(log);

    //Multithreaded test
    log.info("== MULTI-THREADED LOGGING TEST ===");
    threaded_test(log);

    log.info("=== TESTS FINISHED ===");

    return 0;

}