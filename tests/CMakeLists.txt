cmake_minimum_required(VERSION 3.23)

add_executable( logger_tests
    test_logger_basic.cpp
    test_logger_levels.cpp
    test_logger_async.cpp
    test_logger_mock.cpp
)

target_link_libraries( logger_tests
    PRIVATE logger Catch2::Catch2WithMain
)

add_test(
    NAME logger_tests
    COMMAND logger_tests
)