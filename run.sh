#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Remove the build directory if it exists
rm -rf build

# Create a new build directory
mkdir build

# Change to the build directory
cd build

# Run cmake to generate the build files
# Check if the first argument is "ALL_TESTS"
if [ "$1" == "-a" ]; then
    # Run cmake with time-consuming tests enabled
    cmake -DENABLE_TIME_CONSUMING_TESTS=ON ..
else
    # Run cmake with time-consuming tests disabled
    cmake -DENABLE_TIME_CONSUMING_TESTS=OFF ..
fi

# Build the project
make

# Change to the tests directory
cd tests

# Run the tests with verbose output
ctest -V
