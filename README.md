# cpp-coding-exercise
[![C++ Build](https://github.com/DoctorLai/cpp-coding-exercise/actions/workflows/ci.yml/badge.svg)](https://github.com/DoctorLai/cpp-coding-exercise/actions/workflows/ci.yml)
[![Last Commit](https://img.shields.io/github/last-commit/DoctorLai/cpp-coding-exercise)](https://github.com/DoctorLai/cpp-coding-exercise/commits/main)
[![License](https://img.shields.io/github/license/DoctorLai/cpp-coding-exercise)](./LICENSE)
[![Stars](https://img.shields.io/github/stars/DoctorLai/cpp-coding-exercise)](https://github.com/DoctorLai/cpp-coding-exercise/stargazers)
[![Code Style](https://img.shields.io/badge/code%20style-clang--format-blue)](./.clang-format)
[![Commit Activity](https://img.shields.io/github/commit-activity/m/DoctorLai/cpp-coding-exercise)](https://github.com/DoctorLai/cpp-coding-exercise/graphs/commit-activity)
[![Watchers](https://img.shields.io/github/watchers/DoctorLai/cpp-coding-exercise)](https://github.com/DoctorLai/cpp-coding-exercise/watchers)
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg)](./CONTRIBUTING.md)
[![Repo Size](https://img.shields.io/github/repo-size/DoctorLai/cpp-coding-exercise)](https://github.com/DoctorLai/cpp-coding-exercise)
[![Top Language](https://img.shields.io/github/languages/top/DoctorLai/cpp-coding-exercise)](https://github.com/DoctorLai/cpp-coding-exercise/search?l=c%2B%2B)
[![Open PRs](https://img.shields.io/github/issues-pr/DoctorLai/cpp-coding-exercise)](https://github.com/DoctorLai/cpp-coding-exercise/pulls)
[![Forks](https://img.shields.io/github/forks/DoctorLai/cpp-coding-exercise)](https://github.com/DoctorLai/cpp-coding-exercise/forks)
[![Open Issues](https://img.shields.io/github/issues/DoctorLai/cpp-coding-exercise)](https://github.com/DoctorLai/cpp-coding-exercise/issues)
[![Ask DeepWiki](https://deepwiki.com/badge.svg)](https://deepwiki.com/DoctorLai/cpp-coding-exercise)

A collection of **modern C++ coding examples** and small exercises focused on correctness, clarity, and real-world patterns.

This repository is intended as:

* An interview-preparation playground
* A reference for **concurrency, synchronization, low-level, and modern C++ techniques**
* A growing set of **self-contained, buildable examples**
* A collection of practical examples and CLI tools rather than puzzle-only solutions

Current examples include:

* Multithreading
    * [thread-safe-queue](./thread-safe-queue/)
    * [multithread-sum](./multithread-sum/)
* Smart pointers
    * [unique-ptr-basics](./unique-ptr-basics/)
    * [smart-ptr](./smart-ptr/)
* Views
    * [views-zip-enumerate](./views-zip-enumerate/)
* Folding
    * [fold-left-fold-right](./fold-left-fold-right/)
* Parallelism
    * [parallel-transform](./parallel-transform/)
    * [parallel-integral-pi](./parallel-integral-pi/)
* STL and ranges:
    * [ranges-find-in-vector-string](./ranges-find-in-vector-string/)
* Algorithms
    * [integer-factorization](./integer-factorization/)
    * Encoding
        * [rot47](./rot47/)
    * [prefix-sum](./prefix-sum/)
    * [sudoku-solver](./sudoku-solver/)
    * [pi-monte-carlo](./pi-monte-carlo/)
    * [pi](./pi/)
* Data Structures
    * [map-with-unknown-key](./map-with-unknown-key/)
* OOP
    * [virtual-interface](./virtual-interface/)
    * [oop-with-exception](./oop-with-exception/)

---

## Repository Structure

```text
cpp-coding-exercise/
├── Makefile              # top-level dispatcher
├── common.mk             # shared compiler flags
├── <example>/
│   ├── Makefile
│   ├── main.cpp
│   └── tests.sh           # optional behavior tests
└── .github/workflows/
    ├── ci.yml             # builds, sanitizers, tests, and coverage
    └── coverage-comment.yml
```

### Design principles

* **Each example is self-contained**
* Each folder has its own `Makefile`
* The top-level `Makefile` automatically discovers and builds all examples
* No central list to maintain when adding new folders

---

## Prerequisites

```bash
sudo apt update
sudo apt install g++-14 make clang-format gcovr jq libtbb-dev
```

The examples target C++23 and are tested on Ubuntu with GCC 14.

## Building

### Build everything

```bash
make
```

This will recursively build every directory that contains a `Makefile`.

### Build a single example

```bash
cd thread-safe-queue
make
```

---

## Running examples

Runnable examples expose a `run` target:

```bash
make run
```

Top-level `make run` runs all built targets and each available `tests.sh` script.

## Project commands

```bash
make build             # Build every example with the selected sanitizer
make test              # Build as needed, run examples, and execute test scripts
make format            # Format all C and C++ source files
make lint              # Check formatting without modifying files
make coverage          # Generate HTML, XML, JSON, and text coverage reports
make check             # Run formatting and supported sanitizer builds/tests
make clean             # Remove binaries, objects, and coverage artifacts
```

`make coverage` enforces at least 80% line coverage, 80% function coverage, and 70% branch coverage by default.
Override local thresholds with `COVERAGE_MIN`, `COVERAGE_FUNCTION_MIN`, and `COVERAGE_BRANCH_MIN`.

---

## Cleaning

Clean everything:

```bash
make clean
```

Or clean a single example:

```bash
cd thread-safe-queue
make clean
```

---

## Shared build configuration

Common compiler settings live in [common.mk](./common.mk):

```make
CXX      := g++-14
CXXFLAGS := -std=c++23 -Wall -Wextra -Werror
```

Individual examples may extend this, e.g.:

```make
CXXFLAGS += -pthread
```

---

## Sanitizers
AddressSanitizer is enabled by default to detect memory safety problems and leaks.

```bash
# Builds with AddressSanitizer automatically
make

# ThreadSanitizer
make SANITIZE=thread

# UndefinedBehaviorSanitizer
make SANITIZE=undefined

# Select the sanitizer matrix used by make check
make check SANITIZERS="address thread undefined"

# No sanitizers
make SANITIZE=
```

GCC ThreadSanitizer cannot reliably reserve its shadow-memory layout under WSL2 and may terminate before an example
starts with `FATAL: ThreadSanitizer: unexpected memory mapping`. On WSL2, `make check` therefore runs ASan and UBSan by
default. Native Linux and GitHub Actions continue to run ASan, TSan, and UBSan. `SANITIZERS` can override either default.

---

## Clang Format
`clang-format` enforces the repository's C++ style.

```bash
make format            # Apply formatting
make lint              # Check all example directories
./clang-check.sh       # Equivalent recursive standalone check
```

Each example also exposes `make check-format` from its own directory.

---

## Continuous Integration

GitHub Actions builds all examples on:

* Pushes to `main`
* Pull requests targeting `main`

The CI setup requires **no updates** when new example folders are added.

CI runs `make check SANITIZERS="address thread undefined"`, enforces the documented coverage floors, uploads an HTML
coverage report, and posts a coverage summary on pull requests. Each sanitizer configuration starts from a clean build
so compiler flags cannot be silently reused from a previous configuration.

---

## Toolchain

* C++23
* GNU Make
* GCC 14
* clang-format
* gcovr
* Linux (Ubuntu)

---

## Goals (non-goals)

- ✔ Correctness over cleverness
- ✔ Explicit concurrency semantics
- ✔ Minimal dependencies

- ✘ No frameworks
- ✘ No large abstractions
- ✘ No header‑only meta‑programming for its own sake

---

## Contributing and support

See [CONTRIBUTING.md](./CONTRIBUTING.md) before submitting a change. For help, use the channels in
[SUPPORT.md](./SUPPORT.md). Report security concerns privately as described in [SECURITY.md](./SECURITY.md).

Project changes are recorded in [CHANGELOG.md](./CHANGELOG.md), and the repository's data practices are documented in
[PRIVACY.md](./PRIVACY.md).

## License

[MIT](./LICENSE) (unless otherwise stated in a specific example).

---

## Notes

Many examples intentionally focus on **edge cases** and **failure modes** such as data races, lifetime issues, and
ordering bugs. They are meant to be read, built, and experimented with.

Contributions and [discussions](https://github.com/DoctorLai/cpp-coding-exercise/discussions) are welcome.
