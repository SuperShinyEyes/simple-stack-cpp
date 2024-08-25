enable_testing()

option(ENABLE_TIME_CONSUMING_TESTS "Enable time-consuming tests" OFF)

if(ENABLE_TIME_CONSUMING_TESTS)
    add_definitions(-DENABLE_TIME_CONSUMING_TESTS)
endif()

# Find the GoogleTest package
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add the test executable
add_executable(test_linked_list_stack test_linked_list_stack.cpp)
add_executable(test_array_stack test_array_stack.cpp)

# Link the test executable against the GoogleTest libraries
target_link_libraries(test_linked_list_stack GTest::gtest_main simple_stack)
target_link_libraries(test_array_stack GTest::gtest_main simple_stack)

# Register the test with CMake
add_test(NAME ArrayStackTest COMMAND test_array_stack)
add_test(NAME LinkedListStackTest COMMAND test_linked_list_stack)
