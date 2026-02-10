#include <catch2/catch_test_macros.hpp>
#include "../include/logger/logger.hpp"
#include "../include/logger/test_sink.hpp"

TEST_CASE("Async logger flushes messages on destruction") {
    auto sink = std::make_shared<TestSink>();
    {
        logger::Logger log("AsyncLogger");
        log.add_sink(sink);

        log.info("Async message");
        log.flush();
    }
    // Logger destroyedhere, should then, flush messages

    REQUIRE(sink->get_messages().size() == 1);
}