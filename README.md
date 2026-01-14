# cpp-coding-exercise
[![C++ Build](https://github.com/DoctorLai/cpp-coding-exercise/actions/workflows/ci.yml/badge.svg)](https://github.com/DoctorLai/cpp-coding-exercise/actions/workflows/ci.yml)

A collection of **modern C++ coding examples** and small exercises, focused on correctness, clarity, and real‑world patterns.

This repository is intended as:

* A interview‑prep playground
* A reference for **concurrency, synchronization, low‑level and modern C++ techniques**
* A growing set of **self‑contained, buildable examples**
* A collection of more useful examples (and CLI tools) than leetcode puzzles.

Examples include (and will expand to):

* [thread-safe-queue](./thread-safe-queue/)
* Smart pointers
    * [unique-ptr-basics](./unique-ptr-basics/)
    * [smart-ptr](./smart-ptr/)
* Lock‑free / wait‑free data structures
* Views
    * [views-zip-enumerate](./views-zip-enumerate/)
* Atomics and memory ordering
* Folding
    * [fold-left-fold-right](./fold-left-fold-right/)
* RAII and ownership patterns
* Parallelism
    * [parallel-transform](./parallel-transform/)
* Performance‑oriented C++ idioms
* STL and ranges:
    * [ranges-find-in-vector-string](./ranges-find-in-vector-string/)
* Algorithms
    * [integer-factorization](./integer-factorization/)
    * Encoding
        * [rot47](./rot47/)
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
├── thread-safe-queue/
│   ├── Makefile
│   └── main.cpp
├── <future-example>/
│   ├── Makefile
│   └── ...
└── .github/workflows/
    └── ci.yml            # GitHub Actions CI
```

### Design principles

* **Each example is self-contained**
* Each folder has its own `Makefile`
* The top-level `Makefile` automatically discovers and builds all examples
* No central list to maintain when adding new folders

---

## Building

### C++ Version
```bash
sudo apt update
sudo apt install g++-14
```

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

`make run` on top level will run all built targets.

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
CXX      := g++
CXXFLAGS := -std=c++23 -Wall -Wextra
```

Individual examples may extend this, e.g.:

```make
CXXFLAGS += -pthread
```

---

## Address Sanitizer Check
The Address Sanitizer is enabled by default to ensure there is no memory leaks or other memory problems.

```make
# Builds with AddressSanitizer automatically
make

# ThreadSanitizer
make SANITIZE=thread

# UndefinedBehaviorSanitizer
make SANITIZE=undefined

# No sanitizers
make SANITIZE=
```

---

## Clang Format
The `clang-format` is used to ensure the code format.

```bash
./clang-check.sh *.cpp *.hpp
```

At top level, you can do:

```make
make check-format-all
```

At each example directory, you can do:

```make
make check-format
```

---

## Continuous Integration

GitHub Actions automatically builds all examples on:

* Every push
* Every pull request

The CI setup requires **no updates** when new example folders are added.

The CI will perform:
1. `./clang-check.sh *.cpp *.hpp`
2. `make SANITIZE=[address, thread, undefined]`
3. `make run` which will run `make run` for each project and `./tests.sh` if it is present.

---

## Toolchain

* C++23
* GNU Make
* GCC / Clang (CI currently uses GCC)
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

## License

[MIT](./LICENSE) (unless otherwise stated in a specific example).

---

## Notes

Many examples intentionally focus on **edge cases** and **failure modes** (data races, lifetime issues, ordering bugs). They are meant to be read, built, and experimented with.

Contributions and discussions are welcome.
