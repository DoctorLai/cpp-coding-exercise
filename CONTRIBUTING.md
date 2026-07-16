# Contributing

Contributions that add focused C++ examples, improve correctness, or strengthen existing tests are welcome.

## Development setup

Install GCC 14, GNU Make, clang-format, gcovr, and oneTBB on an Ubuntu-compatible system:

```bash
sudo apt update
sudo apt install g++-14 make clang-format gcovr jq libtbb-dev
```

Build and run the complete repository:

```bash
make build
make test
```

## Adding an example

1. Create a descriptive directory containing a `Makefile` and source files.
2. Include `../common.mk` and follow a neighboring example's build targets.
3. Add a `tests.sh` script when the behavior has testable output or error handling.
4. Add the example to the appropriate README category.
5. Keep the example self-contained and avoid dependencies unless they demonstrate an essential concept.

## Before opening a pull request

Run the same checks used by CI:

```bash
make lint
make check
make coverage
```

`make coverage` requires at least 80% aggregate line and function coverage and 70% branch coverage. Add tests for new
behavior rather than lowering the thresholds.

Use a focused commit history and explain the motivation, behavior change, and validation in the pull request. Do not include compiled binaries, object files, or generated coverage reports.

## Reporting problems

Use the bug report template for reproducible defects. Report security vulnerabilities privately according to [SECURITY.md](./SECURITY.md).
