//Benchmark should measure the time required to log a fixed number of messages
//The setup - Test logs 1,000,000 messges, Loglevel type: Info, size of messages 64 bytes, File_sink writes to local SSD
//Result should show a simple table
//Add on README.md a simple analysis of the result from the Benchmark Test, add also eventual limitations of the Test

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <memory>

#include "../include/logger/logger.hpp"
#include "../include/logger/null_sink.hpp"
#include "../include/logger/formatter.hpp"

using clock_type = std::chrono::steady_clock;

int main()
{
    constexpr std::size_t TOTAL_MESSAGES = 1'000'000;
    constexpr std::size_t THREAD_COUNT = 4;
    constexpr std::size_t PER_THREAD = TOTAL_MESSAGES / THREAD_COUNT;

    logger::Logger log("bench");

    //use nullsink will measure pure logging overhead
    auto sink = std::make_shared<logger::NullSink>(
        std::make_unique<logger::SimpleFormatter>()
    );

    log.add_sink(sink);
    log.set_level(logger::LogLevel::Info);

    //For the benchmark to produce the best results, a warmup is recommended
    for (int i = 0; i < 1000; ++i)
        log.info("warmup");
    
    std::vector<std::thread> threads;

    auto start = clock_type::now();

    for (std::size_t i = 0; i < THREAD_COUNT; ++i)
    {
        threads.emplace_back([&log]() {
            for (std::size_t i = 0; i < PER_THREAD; ++i)
                log.info("multithread benchmark message");
                });
    }
    
    for (auto& th : threads)
        th.join();

    auto end = clock_type::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    double seconds = duration / 1000.0;
    double throughput = TOTAL_MESSAGES / seconds;
    
    std::cout << "Threads: " << THREAD_COUNT << "\n";
    std::cout << "Messages: " << TOTAL_MESSAGES << "\n";
    std::cout << "Time: " << seconds << " seconds\n";
    std::cout << "Throughput: " << throughput << " msg/s\n";
}
