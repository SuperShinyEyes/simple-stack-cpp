#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <vector>

#include "simple_stack.h"

TEST(StackArrayTest, HandlesConstructor) {
  StackArray<int> stack(10);
  EXPECT_EQ(stack.getCapacity(), 10);
  EXPECT_TRUE(stack.isEmpty());
}

TEST(StackArrayTest, HandlesPushPop) {
  StackArray<int> stack(10);
  int popped;
  for (int pushed = 0; pushed < 10; pushed++) {
    stack.push(pushed);
    popped = stack.pop();
    EXPECT_EQ(pushed, popped);
  }
}

TEST(StackArrayTest, HandlesPeek) {
  StackArray<int> stack(10);
  for (int pushed = 0; pushed < 10; pushed++) {
    stack.push(pushed);
    EXPECT_EQ(stack.peek(), pushed);
  }
}

TEST(StackArrayTest, HandlesPushPopInteger) {
  StackArray<int> stack(10);
  int popped;
  for (int pushed = 0; pushed < 10; pushed++) {
    stack.push(pushed);
    popped = stack.pop();
    EXPECT_EQ(pushed, popped);
  }
}

TEST(StackArrayTest, HandlesPushPopFloat) {
  StackArray<float> stack(10);
  float popped;
  for (float pushed = 0; pushed < 10; pushed++) {
    stack.push(pushed / 1.0f);
    popped = stack.pop();
    EXPECT_EQ(pushed, popped);
  }
}

TEST(StackArrayTest, HandlesPushPopDouble) {
  StackArray<double> stack(10);
  double popped;
  for (double pushed = 0; pushed < 10; pushed++) {
    stack.push(pushed / 1.0);
    popped = stack.pop();
    EXPECT_EQ(pushed, popped);
  }
}

TEST(StackArrayTest, HandlesPushPopUInt) {
  StackArray<uint> stack(10);
  uint popped;
  for (uint pushed = 0; pushed < 10; pushed++) {
    stack.push(pushed);
    popped = stack.pop();
    EXPECT_EQ(pushed, popped);
  }
}

TEST(StackArrayTest, HandlesPushPopChar) {
  StackArray<char> stack(10);
  char popped;
  std::vector<char> items = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
  for (char pushed : items) {
    stack.push(pushed);
    popped = stack.pop();
    EXPECT_EQ(pushed, popped);
  }
}

TEST(StackArrayTest, HandlesPushPopConstChar) {
  StackArray<const char *> stack(10);
  const char *popped;
  std::vector<const char *> items = {"school", "boy", "girl"};
  for (const char *pushed : items) {
    stack.push(pushed);
    popped = stack.pop();
    EXPECT_EQ(pushed, popped);
  }
}

TEST(StackArrayTest, HandlesPushPopVectorInt) {
  StackArray<std::vector<int>> stack(10);
  std::vector<int> popped;
  std::vector<std::vector<int>> items = {{0, 1, 2, 3}, {2, 3, 4}, {9}};
  for (std::vector<int> pushed : items) {
    stack.push(pushed);
    popped = stack.pop();
    EXPECT_EQ(pushed, popped);
  }
}

int addOne(int a) { return a + 1; }
int addTwo(int a) { return a + 2; }
TEST(StackArrayTest, HandlesPushPopFunctionPointers) {
  typedef int (*FunctionPointerType)(int);
  StackArray<FunctionPointerType> stack(10);
  FunctionPointerType popped;
  std::vector<FunctionPointerType> items = {addOne, addTwo};
  for (FunctionPointerType pushed : items) {
    stack.push(pushed);
    popped = stack.pop();
    EXPECT_EQ(pushed, popped);
  }
}

TEST(StackArrayTest, HandlesInvalidCapacityError) {
  std::vector<int> stack_capacities = {-1000, -10, -1, 0};
  for (int capacity : stack_capacities) {
    EXPECT_THROW(StackArray<int> stack(capacity), StackInvalidCapacityError);
  }
}

TEST(StackArrayTest, HandlesValidSize) {
  std::vector<int> stack_capacities = {1000, 10, 1};
  for (int capacity : stack_capacities) {
    EXPECT_NO_THROW(StackArray<int> stack(capacity));
  }
}

TEST(StackArrayTest, HandlesFullCapacity) {
  int capacity = 100;
  StackArray<int> stack(capacity);
  for (int pushed = 0; pushed < capacity; pushed++) {
    stack.push(pushed);
  }
  EXPECT_TRUE(stack.isFull());
  EXPECT_EQ(stack.getNumberOfElements(), capacity);
}

TEST(StackArrayTest, HandlesEmptyPopError) {
  StackArray<int> stack(10);
  EXPECT_THROW(stack.pop(), StackUnderflowError);
  stack.push(1);
  EXPECT_NO_THROW(stack.pop());
  EXPECT_THROW(stack.pop(), StackUnderflowError);
}

TEST(StackArrayTest, HandlesEmptyPeekError) {
  StackArray<int> stack(10);
  EXPECT_THROW(stack.peek(), StackUnderflowError);
  stack.push(1);
  EXPECT_NO_THROW(stack.peek());
}

TEST(StackArrayTest, HandlesFullError) {
  StackArray<int> stack(10);
  for (int i = 0; i < 10; i++) {
    EXPECT_NO_THROW(stack.push(i));
  }
  EXPECT_THROW(stack.push(1), StackOverflowError);
}

TEST(StackArrayTest, HandlesCopyConstructor) {
  StackArray<int> s1(10);
  for (int i = 0; i < 10; i++) {
    s1.push(i);
  }
  StackArray<int> s2 = s1;
  EXPECT_EQ(s1.getNumberOfElements(), s2.getNumberOfElements());
  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(s1.pop(), s2.pop());
  }
}

TEST(StackArrayTest, HandlesCopyAssignment) {
  StackArray<int> s1(10);
  for (int i = 0; i < 10; i++) {
    s1.push(i);
  }
  StackArray<int> s2(1);
  s2 = s1;
  EXPECT_EQ(s1.getNumberOfElements(), s2.getNumberOfElements());
  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(s1.pop(), s2.pop());
  }
}

TEST(StackArrayTest, HandlesMoveConstructor) {
  int size = 10;
  StackArray<int> s1(size);
  for (int i = 0; i < size; i++) {
    s1.push(i);
  }
  StackArray<int> s2 = std::move(s1);
  EXPECT_EQ(s1.getNumberOfElements(), 0);
  EXPECT_EQ(s1.getCapacity(), 0);
  EXPECT_EQ(s1.getArray(), nullptr);

  EXPECT_EQ(s2.getNumberOfElements(), size);
  EXPECT_EQ(s2.getCapacity(), size);

  for (int i = 9; i > -1; i--) {
    EXPECT_EQ(i, s2.pop());
  }
}

TEST(StackArrayTest, HandlesMoveAssignment) {
  int size = 10;
  StackArray<int> s1(size);
  for (int i = 0; i < size; i++) {
    s1.push(i);
  }
  StackArray<int> s2(1);
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

#ifdef ENABLE_TIME_CONSUMING_TESTS
// Test large elements
TEST(StackArrayTest, HandlesLargeSizeIntVector) {
  // Each vector is size of 400 MB.
  int element_size = 100000000;
  // 20 such vectors -> 8 GB
  int capacity = 20;
  StackArray<std::vector<int>> stack(capacity);
  for (int i = 0; i < capacity; i++) {
    stack.push(std::vector<int>(element_size));
  }
  EXPECT_TRUE(stack.isFull());
  EXPECT_EQ(stack.getNumberOfElements(), capacity);
  EXPECT_EQ(stack.peek().size(), element_size);

  for (int i = 0; i < capacity; i++) {
    EXPECT_EQ(stack.pop().size(), element_size);
  }
  EXPECT_TRUE(stack.isEmpty());
}

// Test mixed size of elements
TEST(StackArrayTest, HandlesMixedSizeIntVector) {
  // This test will consume 10GB of RAM.
  int capacity = 50000;
  StackArray<std::vector<int>> stack(capacity);
  for (int i = 0; i < capacity; i++) {
    stack.push(std::vector<int>(i));
  }
  EXPECT_TRUE(stack.isFull());
  EXPECT_EQ(stack.getNumberOfElements(), capacity);
  EXPECT_EQ(stack.peek().size(), capacity - 1);

  for (int i = 0; i < capacity; i++) {
    EXPECT_EQ(stack.pop().size(), capacity - i - 1);
  }
  EXPECT_TRUE(stack.isEmpty());
}

// Test large stack capacity
TEST(StackArrayTest, HandlesPushPopMany) {
  int capacity = INT_MAX;
  StackArray<int> stack(capacity);
  for (int pushed = 0; pushed < capacity; pushed++) {
    stack.push(pushed);
    EXPECT_EQ(stack.peek(), pushed);
  }
  EXPECT_TRUE(stack.isFull());
  EXPECT_EQ(stack.getNumberOfElements(), capacity);
}

#endif

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
