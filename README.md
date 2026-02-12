# Logger — Modern C++ Logging Library

A lightweight, modern C++ logging library focused on **correctness**, **thread safety**, and **clean API design**.

This project is developed as a portfolio project to deepen my understanding of
modern C++ (C++17), multithreading, and reusable library design, with an emphasis
on production-style constraints and trade-offs.

---

## 🎯 Goals

- Provide a simple and expressive logging API
- Support high-performance logging in multi-threaded applications
- Follow modern C++ best practices (RAII, Rule of Zero/Five)
- Keep the codebase small, readable, and well-documented
- Serve as a reusable foundation for future systems projects

---

## 🚫 Non-Goals

To keep the scope focused, the following features are intentionally **out of scope**:

- Network or remote logging
- Runtime configuration reloading
- GUI tools
- Platform-specific APIs
- Dependency-heavy solutions

---

## 🛠 Technical Overview

- **Language:** C++
- **Standard:** C++17
- **Primary platform:** Linux
- **Build system:** CMake
- **Compiler:** clang++ / g++
- **Threading:** std::thread, std::mutex, std::condition_variable
- **Warnings:** -Wall -Wextra -Wpedantic
- **Formatting:** clang-format
- **Static Analysis:** clang-tidy
- **Testing Framework:** Catch2

This toolchain was chosen to prioritize portability, modern C++ features,
and strong compile-time diagnostics during development.

---

## 📦 Features

### Implemented
- Log levels: `TRACE`, `DEBUG`, `INFO`, `WARN`, `ERROR`
- Clean, object-oriented logging API
- Multiple output sinks:
  - Console sink
  - File sink
  - Null sink (for benchmarking)
- Timestamped log messages
- Pluggable formatting system
- Thread-safe logging API
- **Asynchronous logging using a background worker thread**
- Background working trhead
- Graceful shutdown with guaranteed log flushing (RAII)
- Unit tests (Catch2)
- Single-thread and multi-thread benckmarks

### Planned
- Configurable formatting options
- Bounded queue / backpressure handling
- Unit tests
- Benchmarks (sync vs async logging)

---

## 🧱 Project Structure

```
logger/
├── include/
│ └── logger/
│ ├── logger.hpp
│ ├── log_level.hpp
│ ├── log_message.hpp
│ ├── sink.hpp
│ ├── console_sink.hpp
│ ├── file_sink.hpp
│ ├── null_sink.hpp
│ └── formatter.hpp
├── src/
│ ├── logger.cpp
│ ├── sink.cpp
│ ├── console_sink.cpp
│ ├── file_sink.cpp
│ ├── null_sink.cpp
│ └── formatter.cpp
├── examples/
│ └── basic.cpp
├── benchmark/
│ └── logger_benchmark.cpp
├── tests/ # planned
└── CMakeLists.txt
```
---

## 🧠 Design Philosophy

- Prefer clarity over cleverness
- Make ownership explicit
- Avoid global state
- Fail loudly during development
- Optimize only after measuring

Design decisions and trade-offs are documented as the project evolves.

---

## 🧵 Threading Model (Asynchronous)

Logging is **asynchronous by default** and follows a classic
**producer–consumer** design.

### Overview

- Logging calls (`info()`, `warn()`, etc.) act as **producers**
- A single background worker thread acts as the **consumer**
- Log messages are passed through a thread-safe queue

```
Thread 1 ─┐
Thread 2 ─┤
Thread 3 ─┤  log() calls (producers)
  ...    ─┤
Thread N ─┘
          │
          ▼
   Thread-safe queue
          │
          ▼
Background worker thread (consumer)
          │
          ▼
     Sink writes
```

---

### Key properties

- Logging calls are **non-blocking** and return immediately
- A `std::condition_variable` is used to avoid busy-waiting
- A single worker thread serializes all sink writes
- The logger destructor:
  - Signals shutdown
  - Flushes all remaining messages
  - Joins the worker thread (RAII)

This design minimizes contention in hot paths while preserving correctness
and predictable shutdown behavior.

---

## 📊 Benchmark Results

Benchmarks were run in **Release mode** on Linux.

### Single-thread (1,000,000 messages)

~125,000 msg/s


### Multi-thread (4 producer threads, 1,000,000 total messages)

~430,000 – 438,000 msg/s

### Scaling Analysis

| Threads | Throughput |
|----------|------------|
| 1        | ~125k msg/s |
| 4        | ~435k msg/s |

The system achieves ~87% of ideal linear scaling (500k expected).

This indicates:

- Moderate mutex contention
- Good parallelization of formatting work
- Worker thread keeps up under load
- Async architecture behaves correctly under concurrency

---

## 🔍 Performance Investigation

Several experiments were conducted:

- Replaced FileSink with NullSink
- Removed timestamp formatting
- Measured single-thread vs multi-thread performance

Findings:

- File I/O was not the primary bottleneck (OS buffering helps)
- Timestamp formatting was not dominant
- The main overhead comes from:
  - Mutex locking per message
  - Condition variable notifications
  - Context switching

This confirms the design trade-off:

> Simplicity and correctness over maximum throughput.

---

## ⚖️ Design Trade-offs

- A single background thread simplifies reasoning and guarantees ordering
- Configuration changes (adding sinks, changing log level) are expected to
  occur during initialization, not at runtime
- The queue is currently unbounded to keep the design simple
  (bounded queues and backpressure are planned)

These trade-offs favor **simplicity, safety, and debuggability** over maximum
throughput.

---

## 🚧 Project Status

**Phase 0 — Planning**
- [x] Define project scope
- [x] Choose toolchain

**Phase 1 — Project Skeleton**
- [x] CMake setup
- [x] Project structure
- [x] Example executable

**Phase 2 — Core API Design**
- [x] Logger public API
- [x] Sink abstraction
- [x] Formatter abstraction

**Phase 3 — Single-Threaded Implementation**
- [x] Console sink
- [x] File sink
- [x] Timestamped formatting
- [x] Working example

**Phase 4 — Concurrency**
- [x] Mutex-protected logging
- [x] Multi-threaded stress test
- [x] Asynchronous logging with worker thread
- [x] Graceful shutdown and log flushing

**Phase 5 — Testing & Polish**
- [x] Unit tests
- [x] Benchmarks
- [x] Documentation refinements

---

## 🚀 Possible Future Improvements

This project can be significantly extended in the future:

### Performance Improvements

- Bounded queue with backpressure policy
- Message batching in worker
- Lock-free ring buffer
- Reduced notification frequency
- Thread-local buffers
- Use of `fmt` instead of `std::ostringstream`

### Features

- Structured logging (JSON output)
- Compile-time log level filtering
- Sink-level log filtering
- Configuration system
- Log rotation
- Metrics / monitoring hooks

### Advanced Topics

- MPMC queue implementation
- Zero-allocation logging path
- Automated benchmark suite
- Integration with profiling tools (`perf`, `valgrind`, etc.)

---

## 📄 License

This project is developed for portfolio and learning purposes.  
License to be defined.
