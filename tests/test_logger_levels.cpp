#include <catch2/catch_test_macros.hpp>
#include "../include/logger/logger.hpp"
#include "../include/logger/test_sink.hpp"
#include "../include/logger/log_level.hpp"

TEST_CASE("Logger respects log level filtering") {
    logger::Logger log("TestLogger");

    auto sink = std::make_shared<TestSink>();
    log.add_sink(sink);

    log.set_level(logger::LogLevel::Warn);

    log.info("Should not appear");
    log.warn("Should appear");
    log.flush();

    REQUIRE(sink->get_messages().size() == 1);
    REQUIRE(sink->get_messages()[0].message == "Should appear");
}