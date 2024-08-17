enable_testing()

# Find the GoogleTest package
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add the test executable
add_executable(test_simple_stack test_simple_stack.cpp)

# Link the test executable against the GoogleTest libraries
target_link_libraries(test_simple_stack GTest::gtest_main simple_stack)

# Register the test with CMake
add_test(NAME SimpleStackTest COMMAND test_simple_stack)
