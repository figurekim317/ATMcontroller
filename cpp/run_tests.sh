#!/bin/bash
# run_tests.sh

# Exit immediately if a command exits with a non-zero status.
set -e

# Navigate to the script's directory
cd "$(dirname "$0")"

# Build the project using Makefile
make

# Run the test executable
./test_atm

# (Optional) Clean the build files after testing
# Uncomment the following line if you wish to clean up
# make clean
