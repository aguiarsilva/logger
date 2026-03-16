cmake_minimum_required(VERSION 3.23)

project(logger
	VERSION 0.1.0
	DESCRIPTION "C++ logging library"
	LANGUAGES CXX
)

enable_testing()

add_subdirectory(external/Catch2)
add_subdirectory(tests)

#  Set C++ standard

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#  add library target

add_library(logger STATIC
	src/logger.cpp
	src/sink.cpp
	src/formatter.cpp
	src/console_sink.cpp
	src/file_sink.cpp
	src/test_sink.cpp
	src/null_sink.cpp
)

target_include_directories(logger
	PUBLIC
		${PROJECT_SOURCE_DIR}/include
)

# Compiler flags for warnings
target_compile_options(logger
	PRIVATE
		-Wall
		-Wextra
		-Wpedantic
)

# Example executable
add_executable(logger_example
	examples/basic.cpp
)

add_executable(logger_benchmark
    benchmark/benchmark_logger.cpp
)

# add target to link the libraries
target_link_libraries(logger_example
	PRIVATE logger
)

target_link_libraries(logger_benchmark
    PRIVATE logger
)
