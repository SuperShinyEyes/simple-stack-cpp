#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <vector>

#include "simple_stack.h"

TEST(StackListTest, HandlesConstructor) {
  StackList<int> stack(10);
  EXPECT_EQ(stack.getCapacity(), 10);
  EXPECT_TRUE(stack.isEmpty());
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

TEST(StackListTest, HandlesPeek) {
  StackList<int> stack(10);
  for (int pushed = 0; pushed < 10; pushed++) {
    stack.push(pushed);
    EXPECT_EQ(stack.peek(), pushed);
  }
}

TEST(StackListTest, HandlesInvalidCapacityError) {
  std::vector<int> stack_capacities = {-1000, -10, -1, 0};
  for (int capacity : stack_capacities) {
    EXPECT_THROW(StackList<int> stack(capacity), StackInvalidCapacityError);
  }
}

TEST(StackListTest, HandlesValidSize) {
  std::vector<int> stack_capacities = {1000, 10, 1};
  for (int capacity : stack_capacities) {
    EXPECT_NO_THROW(StackList<int> stack(capacity));
  }
}

TEST(StackListTest, HandlesFullCapacity) {
  int capacity = 100;
  StackList<int> stack(capacity);
  for (int pushed = 0; pushed < capacity; pushed++) {
    stack.push(pushed);
  }
  EXPECT_TRUE(stack.isFull());
  EXPECT_EQ(stack.getNumberOfElements(), capacity);
}

TEST(StackListTest, HandlesEmptyPopError) {
  StackList<int> stack(10);
  EXPECT_THROW(stack.pop(), StackUnderflowError);
  stack.push(1);
  EXPECT_NO_THROW(stack.pop());
  EXPECT_THROW(stack.pop(), StackUnderflowError);
}

TEST(StackListTest, HandlesEmptyPeekError) {
  StackList<int> stack(10);
  EXPECT_THROW(stack.peek(), StackUnderflowError);
  stack.push(1);
  EXPECT_NO_THROW(stack.peek());
}

TEST(StackListTest, HandlesFullError) {
  StackList<int> stack(10);
  for (int i = 0; i < 10; i++) {
    EXPECT_NO_THROW(stack.push(i));
  }
  EXPECT_THROW(stack.push(1), StackOverflowError);
}

TEST(StackListTest, HandlesCopyConstructor) {
  StackList<int> s1(10);
  for (int i = 0; i < 10; i++) {
    s1.push(i);
  }
  StackList<int> s2 = s1;
  EXPECT_EQ(s1.getNumberOfElements(), s2.getNumberOfElements());
  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(s1.pop(), s2.pop());
  }
}

TEST(StackListTest, HandlesCopyAssignment) {
  StackList<int> s1(10);
  for (int i = 0; i < 10; i++) {
    s1.push(i);
  }
  StackList<int> s2(1);
  s2 = s1;
  EXPECT_EQ(s1.getNumberOfElements(), s2.getNumberOfElements());
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
  EXPECT_EQ(s1.getNumberOfElements(), 0);
  EXPECT_EQ(s1.getCapacity(), 0);
  EXPECT_EQ(s1.getArray(), nullptr);

  EXPECT_EQ(s2.getNumberOfElements(), size);
  EXPECT_EQ(s2.getCapacity(), size);

  for (int i = 9; i > -1; i--) {
    EXPECT_EQ(i, s2.pop());
  }
}

TEST(StackListTest, HandlesMoveAssignment) {
  int size = 10;
  StackList<int> s1(size);
  for (int i = 0; i < size; i++) {
    s1.push(i);
  }
  StackList<int> s2(1);
  s2 = std::move(s1);
  EXPECT_EQ(s1.getNumberOfElements(), 0);
  EXPECT_EQ(s1.getCapacity(), 0);
  EXPECT_EQ(s1.getArray(), nullptr);

  EXPECT_EQ(s2.getNumberOfElements(), size);
  EXPECT_EQ(s2.getCapacity(), size);

  for (int i = 9; i > -1; i--) {
    EXPECT_EQ(i, s2.pop());
  }
}

// Test large stack capacity

// TEST(StackListTest, HandlesPushPopMany) {
//   int capacity = INT_MAX;
//   StackList<int> stack(capacity);
//   for (int pushed = 0; pushed < capacity; pushed++) {
//     stack.push(pushed);
//     EXPECT_EQ(stack.peek(), pushed);
//   }
//   EXPECT_TRUE(stack.isFull());
//   EXPECT_EQ(stack.getNumberOfElements(), capacity);
// }

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
