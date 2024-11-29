#!/bin/bash
# run_tests.sh

# Exit immediately if a command exits with a non-zero status.
set -e

# Navigate to the script's directory
cd "$(dirname "$0")"

# Run unit tests
python -m unittest discover -s tests -p 'test_*.py'
