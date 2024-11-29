#!/bin/bash

# Exit immediately if a command exits with a non-zero status.
set -e

# Define colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color

# Navigate to the script's directory
cd "$(dirname "$0")"

# Print starting message
echo -e "${YELLOW}Starting build and test process...${NC}"

# Build the project using Makefile
if make; then
    echo -e "${GREEN}Build successful!${NC}"
else
    echo -e "${RED}Build failed.${NC}"
    exit 1
fi

# Run the test executable
if ./test_atm; then
    echo -e "${GREEN}All tests passed successfully!${NC}"
else
    echo -e "${RED}Tests failed.${NC}"
    exit 1
fi

# (Optional) Clean the build files after testing
if [[ $1 == "--clean" ]]; then
    echo -e "${YELLOW}Cleaning build files...${NC}"
    make clean
    echo -e "${GREEN}Clean complete.${NC}"
fi

# Print finishing message
echo -e "${GREEN}Build and test process completed.${NC}"
