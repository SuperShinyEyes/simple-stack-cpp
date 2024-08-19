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
    EXPECT_EQ(stack.getSize(), 10);
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

TEST(StackListTest, HandlesCopyConstructor) {
    StackList<int> s1(10);
    for (int i = 0; i < 10; i++) {
        s1.push(i);
    }
    StackList<int> s2 = s1;
    EXPECT_EQ(s1.index, s2.index);
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(s1.pop(), s2.pop());
    }
}

TEST(StackListTest, HandlesMoveConstructor) {
    int size = 10;
    StackList<int> s1(size);
    for (int i = 0; i < size; i++) {
        s1.push(i);
    }
    StackList<int> s2 = std::move(s1);
    EXPECT_EQ(s1.index, 0);
    EXPECT_EQ(s1.getSize(), 0);
    EXPECT_EQ(s1.getStack(), nullptr);

    EXPECT_EQ(s2.index, size);
    EXPECT_EQ(s2.getSize(), size);
    
    for (int i = 9; i > -1; i--) {
        EXPECT_EQ(i, s2.pop());
    }
}

// LinkedList

TEST(StackLinkedListTest, HandlesConstructor) {
    StackLinkedList<int> stack(10);
    EXPECT_EQ(stack.getSize(), 10);
    EXPECT_EQ(stack.getLength(), 0);
}

TEST(StackLinkedListTest, HandlesPushPop) {
    StackLinkedList<int> stack(10);
    int popped; 
    for (int pushed = 0; pushed < 10; pushed++) {
        stack.push(pushed);
        popped = stack.pop();
        EXPECT_EQ(pushed, popped);
    }
}

// TEST(StackLinkedListTest, HandlesInvalidSizeError) {
//     std::vector<int> stack_sizes = {-1000, -10, -1, 0};
//     for (int size : stack_sizes){
//         EXPECT_THROW(StackLinkedList<int> stack(size), StackInvalidSizeError);
//     }
// }

// TEST(StackLinkedListTest, HandlesValidSize) {
//     std::vector<int> stack_sizes = {1000, 10, 1};
//     for (int size : stack_sizes){
//         EXPECT_NO_THROW(StackLinkedList<int> stack(size));
//     }
// }

// TEST(StackLinkedListTest, HandlesEmptyError) {
//     StackLinkedList<int> stack(10);
//     EXPECT_THROW(stack.pop(), StackEmptyError);
//     stack.push(1);
//     EXPECT_NO_THROW(stack.pop());
//     EXPECT_THROW(stack.pop(), StackEmptyError);
// }

// TEST(StackLinkedListTest, HandlesFullError) {
//     StackLinkedList<int> stack(10);
//     for (int i = 0; i < 10; i++) {
//         EXPECT_NO_THROW(stack.push(i));
//     }
//     EXPECT_THROW(stack.push(1), StackFullError);
// }

// TEST(StackLinkedListTest, HandlesCopyConstructor) {
//     StackLinkedList<int> s1(10);
//     for (int i = 0; i < 10; i++) {
//         s1.push(i);
//     }
//     StackLinkedList<int> s2 = s1;
//     EXPECT_EQ(s1.index, s2.index);
//     for (int i = 0; i < 10; i++) {
//         EXPECT_EQ(s1.pop(), s2.pop());
//     }
// }

// TEST(StackLinkedListTest, HandlesMoveConstructor) {
//     int size = 10;
//     StackLinkedList<int> s1(size);
//     for (int i = 0; i < size; i++) {
//         s1.push(i);
//     }
//     StackLinkedList<int> s2 = std::move(s1);
//     EXPECT_EQ(s1.index, 0);
//     EXPECT_EQ(s1.getSize(), 0);
//     EXPECT_EQ(s1.getStack(), nullptr);

//     EXPECT_EQ(s2.index, size);
//     EXPECT_EQ(s2.getSize(), size);
    
//     for (int i = 9; i > -1; i--) {
//         EXPECT_EQ(i, s2.pop());
//     }
// }

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
