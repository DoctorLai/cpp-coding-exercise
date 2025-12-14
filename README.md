# cpp-coding-exercise
[![C++ Build](https://github.com/DoctorLai/cpp-coding-exercise/actions/workflows/ci.yml/badge.svg)](https://github.com/DoctorLai/cpp-coding-exercise/actions/workflows/ci.yml)

A collection of **modern C++ coding examples** and small exercises, focused on correctness, clarity, and real‑world patterns.

This repository is intended as:

* A interview‑prep playground
* A reference for **concurrency, synchronization, low‑level and modern C++ techniques**
* A growing set of **self‑contained, buildable examples**
* A collection of more useful examples than leetcode puzzles.

Examples include (and will expand to):

* [thread-safe-queue](./thread-safe-queue/)
* Smart pointers
    * [unique-ptr-basics](./unique-ptr-basics/)
* Lock‑free / wait‑free data structures
* Atomics and memory ordering
* RAII and ownership patterns
* Performance‑oriented C++ idioms

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

This keeps CI safe (build-only by default) while allowing local execution.

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

Common compiler settings live in `common.mk`:

```make
CXX      := g++
CXXFLAGS := -std=c++20 -O2 -Wall -Wextra
```

Individual examples may extend this, e.g.:

```make
CXXFLAGS += -pthread
```

---

## Continuous Integration

GitHub Actions automatically builds all examples on:

* Every push
* Every pull request

The CI setup requires **no updates** when new example folders are added.

---

## Toolchain

* C++20
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
