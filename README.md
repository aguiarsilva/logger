# Logger — Modern C++ Logging Library

A lightweight, modern C++ logging library focused on **correctness**, **thread safety**, and **clean API design**.

This project is developed as a portfolio project to deepen my understanding of
modern C++ (C++17), multithreading, and library design.

---

## 🎯 Goals

- Provide a simple and expressive logging API
- Ensure thread-safe logging in multi-threaded applications
- Follow modern C++ best practices (RAII, Rule of Zero/Five)
- Keep the codebase small, readable, and well-documented

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
- **Debugger:** lldb / gdb
- **Warnings:** -Wall -Wextra -Werror
- **Formatting:** clang-format
- **Static Analysis:** clang-tidy (optional)
- **Testing Framework:** Catch2 (planned)

This toolchain was chosen to prioritize portability, modern C++ features, 
and strong compile-time diagnostics during development.

---

## 📦 Planned Features

- Log levels: `TRACE`, `DEBUG`, `INFO`, `WARN`, `ERROR`
- Multiple output sinks:
  - Console
  - File
- Timestamped log messages
- Configurable log formatting
- Thread-safe logging
- Optional asynchronous logging

---

## 🧱 Project Structure (planned)
```
logger/
├── include/
│ └── logger/
├── src/
├── examples/
├── tests/
└── CMakeLists.txt
```
---

## 🧠 Design Philosophy

- Prefer clarity over cleverness
- Make ownership explicit
- Avoid global state
- Fail loudly during development
- Optimize only after measuring

Design decisions and trade-offs will be documented as the project evolves.

---

## 🚧 Project Status

**Phase 0 — Planning**

- [x] Define project scope
- [x] Choose toolchain
- [ ] Project skeleton
- [ ] Core logging API
- [ ] Thread-safe implementation
- [ ] Tests
- [ ] Documentation & benchmarks

---

## 📄 License

This project is for portfolio purposes.
License to be defined.
