#include <catch2/catch_test_macros.hpp>
#include "../include/logger/logger.hpp"
#include "../include/logger/test_sink.hpp"

TEST_CASE("Logger handles concurrent logging") {
    logger::Logger log("ConcurrentLogger");

    auto sink = std::make_shared<TestSink>();
    log.add_sink(sink);

    const int threads = 4;
    const int per_thread = 50;

    std::vector<std::thread> workers;

    for (int i = 0; i < threads; ++i) {
        workers.emplace_back([&]() {
            for (int j = 0; j < per_thread; ++j)
                log.info("msg");
        });
    }

    for (auto& t: workers)
        t.join();

    log.flush();    

    REQUIRE(sink->get_messages().size() == threads * per_thread);
}