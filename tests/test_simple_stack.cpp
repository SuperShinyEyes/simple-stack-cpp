#include <gtest/gtest.h>
#include "simple_stack.h"

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
    int pushed = 10;
    stack.push(pushed);
    int popped = stack.pop(); 
    EXPECT_EQ(pushed, popped);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
