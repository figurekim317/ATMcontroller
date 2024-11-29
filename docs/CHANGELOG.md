# Changelog

## [1.0.3] - 2024-11-29
### Added
- Enhanced `run_tests.sh`:
  - Added color-coded logging for better readability.
  - Improved error handling with descriptive success and failure messages.
- Refined `Dockerfile`:
  - Optimized for caching by separating dependencies from source code during build.
  - Added logging and improved Python environment configuration (`PYTHONUNBUFFERED`).
- Improved `Utility.cpp`:
  - Added log file support for `logMessage` function.
  - Standardized log format for consistency across console and file outputs.
- Added support for Luhn algorithm validation in `Card` class (Python and C++).

### Changed
- Refactored `ATMController` Python unit tests:
  - Added helper methods to reduce code duplication.
  - Enhanced test names for better traceability.
  - Improved edge case coverage (e.g., incorrect PIN, card ejection handling).
- Updated Makefile:
  - Introduced stricter compiler flags for improved code quality.
  - Organized build artifacts into dedicated `bin/` and `obj/` directories.
- Improved README documentation:
  - Added instructions for running tests in a Docker environment.
  - Included detailed setup instructions for Python and C++ projects.

---

## [1.0.2] - 2024-11-29
### Added
- `run_tests.sh` script to automate the build and testing process with optional cleaning functionality.
- Color-coded logging in `run_tests.sh` for enhanced output clarity.
- Enhanced Dockerfile for containerized testing.
- Improved Makefile structure:
  - Added support for `test` target to simplify test execution.
  - Organized build outputs into `obj/` and `bin/` directories.

### Changed
- Refactored all test functions in `test_atm.cpp`:
  - Added detailed log messages for each test.
  - Improved error handling and failure messages.
- Updated Makefile for stricter compiler flags (`-Wpedantic`, `-Werror`).
- Refined Dockerfile for efficient file copying and caching.

---

## [1.0.1] - 2024-11-29
### Added
- `utils.py` and `config.py` for shared utilities and configurations.
- `Utility.h` and `Utility.cpp` for reusable C++ utilities.

### Changed
- Enhanced README files with detailed explanations.

---

## [1.0.0] - 2024-11-29
### Added
- Initial directory structure and base files for Python and C++.
