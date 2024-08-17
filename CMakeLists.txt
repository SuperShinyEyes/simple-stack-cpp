cmake_minimum_required(VERSION 3.10)
project(SimpleStack)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the main code directory
add_subdirectory(src)

# Add the tests directory
add_subdirectory(tests)
