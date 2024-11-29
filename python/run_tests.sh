#!/bin/bash

# Exit immediately if a command exits with a non-zero status.
set -e

# Define colors for better readability
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Navigate to the script's directory
cd "$(dirname "$0")"

echo -e "${GREEN}Starting unit tests...${NC}"

# Run unit tests
if python -m unittest discover -s tests -p 'test_*.py'; then
    echo -e "${GREEN}All tests passed successfully!${NC}"
else
    echo -e "${RED}Some tests failed. Please check the logs above.${NC}"
    exit 1
fi
