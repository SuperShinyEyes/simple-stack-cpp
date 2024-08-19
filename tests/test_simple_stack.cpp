#include <gtest/gtest.h>
#include "simple_stack.h"
#include <vector>

TEST(AdditionTest, HandlesPositiveInput) {
    EXPECT_EQ(add(1, 2), 3);
}

TEST(AdditionTest, HandlesNegativeInput) {
    EXPECT_EQ(add(-1, -1), -2);
}

TEST(StackListTest, HandlesConstructor) {
    StackList<int> stack(10);
    EXPECT_EQ(stack.get_size(), 10);
}

TEST(StackListTest, HandlesPushPop) {
    StackList<int> stack(10);
    int popped; 
    for (int pushed = 0; pushed < 10; pushed++) {
        stack.push(pushed);
        popped = stack.pop();
        EXPECT_EQ(pushed, popped);
    }
}

TEST(StackListTest, HandlesInvalidSizeError) {
    std::vector<int> stack_sizes = {-1000, -10, -1, 0};
    for (int size : stack_sizes){
        EXPECT_THROW(StackList<int> stack(size), StackInvalidSizeError);
    }
}

TEST(StackListTest, HandlesValidSize) {
    std::vector<int> stack_sizes = {1000, 10, 1};
    for (int size : stack_sizes){
        EXPECT_NO_THROW(StackList<int> stack(size));
    }
}

TEST(StackListTest, HandlesEmptyError) {
    StackList<int> stack(10);
    EXPECT_THROW(stack.pop(), StackEmptyError);
    stack.push(1);
    EXPECT_NO_THROW(stack.pop());
    EXPECT_THROW(stack.pop(), StackEmptyError);
}

TEST(StackListTest, HandlesFullError) {
    StackList<int> stack(10);
    for (int i = 0; i < 10; i++) {
        EXPECT_NO_THROW(stack.push(i));
    }
    EXPECT_THROW(stack.push(1), StackFullError);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
