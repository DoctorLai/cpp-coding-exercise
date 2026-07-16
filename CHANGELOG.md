# Changelog

All notable changes to this repository are documented in this file.

The project uses date-based versions because it does not publish a package or release artifact.

## [2026-07-16]

### Added

- Make targets for formatting, linting, testing, sanitizer checks, and coverage.
- Aggregate coverage gates of 80% for lines and functions and 70% for branches, with HTML, XML, JSON, and text reports.
- Secure pull request coverage comments and uploaded coverage artifacts.
- Immutable commit pins for third-party GitHub Actions used by CI.
- Contribution, support, security, privacy, pull request, and dependency update policies.

### Changed

- CI now performs clean builds for AddressSanitizer, ThreadSanitizer, and UndefinedBehaviorSanitizer.
- The CI ThreadSanitizer job now builds a pinned, sanitizer-aware oneTBB to avoid reports caused by an uninstrumented
	parallel STL backend.
- UndefinedBehaviorSanitizer findings now terminate the affected test immediately.
- Local WSL2 checks skip the unsupported GCC ThreadSanitizer runtime by default while native Linux CI retains it.
- Example link rules now honor shared linker flags.
- Pi tests validate numeric output without requiring `bc`.
- Sudoku and smart pointer examples print real line breaks instead of escaped text.
- README build instructions, CI documentation, project commands, and badges were expanded and corrected.
