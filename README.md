# Logger — Modern C++ Logging Library

A lightweight, modern C++ logging library focused on **correctness**, **thread safety**, and **clean API design**.

This project is developed as a portfolio project to deepen my understanding of
modern C++ (C++17), multithreading, and reusable library design.

---

## 🎯 Goals

- Provide a simple and expressive logging API
- Ensure thread-safe logging in multi-threaded applications
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
- **Threading:** std::thread, std::mutex  
- **Debugger:** lldb / gdb
- **Warnings:** -Wall -Wextra -Wpedantic
- **Formatting:** clang-format
- **Static Analysis:** clang-tidy (optional)
- **Testing Framework:** Catch2 (planned)

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
- Timestamped log messages
- Pluggable formatting system
- Thread-safe logging using a single mutex
- Graceful handling of concurrent logging calls

### Planned
- Asynchronous logging using a background worker thread
- Configurable formatting options
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
│ └── formatter.hpp
├── src/
│ ├── logger.cpp
│ ├── sink.cpp
│ ├── console_sink.cpp
│ ├── file_sink.cpp
│ └── formatter.cpp
├── examples/
│ └── basic.cpp
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

## 🧵 Threading Model (Current)

The current implementation ensures thread safety using a **single `std::mutex`**
inside the `Logger` class.

- All logging operations (level checks, formatting, sink writes) are protected
  by a single critical section.
- Configuration changes (adding sinks, changing log level) are also synchronized.
- This approach prioritizes **correctness, simplicity, and ease of reasoning**
  over raw performance.

This design serves as a safe baseline before introducing asynchronous logging.

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

**Phase 4 — Thread Safety**
- [x] Mutex-protected logging
- [x] Multi-threaded stress test
- [ ] Asynchronous logging (planned)

**Phase 5 — Testing & Polish**
- [ ] Unit tests
- [ ] Benchmarks
- [ ] Documentation refinements

---

## 📄 License

This project is for portfolio purposes.  
License to be defined.
