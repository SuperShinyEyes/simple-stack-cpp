#include <gtest/gtest.h>

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "simple_stack.h"

TEST(StackLinkedListTest, HandlesSmartPointer) {
  std::unique_ptr<int> score;
  EXPECT_EQ(score, nullptr);
}
TEST(StackLinkedListTest, HandlesConstructor) {
  StackLinkedList<int> stack(10);
  EXPECT_EQ(stack.getCapacity(), 10);
  EXPECT_TRUE(stack.isEmpty());
}

TEST(StackLinkedListTest, HandlesPushSize) {
  int capacity = 10;
  StackLinkedList<int> stack(capacity);
  for (int pushed = 0; pushed < capacity; pushed++) {
    stack.push(pushed);
  }
  EXPECT_EQ(stack.getCapacity(), capacity);
  EXPECT_EQ(stack.getNumberOfElements(), capacity);
}

TEST(StackLinkedListTest, HandlesPeek) {
  int size = 10;
  StackLinkedList<int> s1(size);
  for (int i = 0; i < size; i++) {
    s1.push(i);
    EXPECT_EQ(s1.peek(), i);
  }
}

TEST(StackLinkedListTest, HandlesPushPopSize) {
  int capacity = 10;
  StackLinkedList<int> stack(capacity);
  for (int pushed = 0; pushed < capacity; pushed++) {
    stack.push(pushed);
  }
  int num_pops = 5;
  for (int pushed = 0; pushed < num_pops; pushed++) {
    stack.pop();
  }
  EXPECT_EQ(stack.getCapacity(), capacity);
  EXPECT_EQ(stack.getNumberOfElements(), capacity - num_pops);
}

TEST(StackLinkedListTest, HandlesPushPopInteger) {
  StackLinkedList<int> stack(10);
  int popped;
  for (int pushed = 0; pushed < 10; pushed++) {
    stack.push(pushed);
    popped = stack.pop();
    EXPECT_EQ(pushed, popped);
  }
}

TEST(StackLinkedListTest, HandlesPushPopFloat) {
  StackLinkedList<float> stack(10);
  float popped;
  for (float pushed = 0; pushed < 10; pushed++) {
    stack.push(pushed / 1.0f);
    popped = stack.pop();
    EXPECT_EQ(pushed, popped);
  }
}

TEST(StackLinkedListTest, HandlesPushPopDouble) {
  StackLinkedList<double> stack(10);
  double popped;
  for (double pushed = 0; pushed < 10; pushed++) {
    stack.push(pushed / 1.0);
    popped = stack.pop();
    EXPECT_EQ(pushed, popped);
  }
}

TEST(StackLinkedListTest, HandlesPushPopUInt) {
  StackLinkedList<uint> stack(10);
  uint popped;
  for (uint pushed = 0; pushed < 10; pushed++) {
    stack.push(pushed);
    popped = stack.pop();
    EXPECT_EQ(pushed, popped);
  }
}

TEST(StackLinkedListTest, HandlesPushPopChar) {
  StackLinkedList<char> stack(10);
  char popped;
  std::vector<char> items = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
  for (char pushed : items) {
    stack.push(pushed);
    popped = stack.pop();
    EXPECT_EQ(pushed, popped);
  }
}

TEST(StackLinkedListTest, HandlesPushPopConstChar) {
  StackLinkedList<const char *> stack(10);
  const char *popped;
  std::vector<const char *> items = {"school", "boy", "girl"};
  for (const char *pushed : items) {
    stack.push(pushed);
    popped = stack.pop();
    EXPECT_EQ(pushed, popped);
  }
}

TEST(StackLinkedListTest, HandlesPushPopVectorInt) {
  StackLinkedList<std::vector<int>> stack(10);
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
TEST(StackLinkedListTest, HandlesPushPopFunctionPointers) {
  typedef int (*FunctionPointerType)(int);
  StackLinkedList<FunctionPointerType> stack(10);
  FunctionPointerType popped;
  std::vector<FunctionPointerType> items = {addOne, addTwo};
  for (FunctionPointerType pushed : items) {
    stack.push(pushed);
    popped = stack.pop();
    EXPECT_EQ(pushed, popped);
  }
}

TEST(StackLinkedListTest, HandlesInvalidCapacityError) {
  std::vector<int> stack_capacities = {-1000, -10, -1, 0};
  for (int capacity : stack_capacities) {
    EXPECT_THROW(StackLinkedList<int> stack(capacity),
                 StackInvalidCapacityError);
  }
}

TEST(StackLinkedListTest, HandlesValidSize) {
  std::vector<int> stack_capacities = {1000, 10, 1};
  for (int capacity : stack_capacities) {
    EXPECT_NO_THROW(StackLinkedList<int> stack(capacity));
  }
}

TEST(StackLinkedListTest, HandlesFullCapacity) {
  int capacity = 100;
  StackLinkedList<int> stack(capacity);
  for (int pushed = 0; pushed < capacity; pushed++) {
    stack.push(pushed);
  }
  EXPECT_TRUE(stack.isFull());
  EXPECT_EQ(stack.getNumberOfElements(), capacity);
}

TEST(StackLinkedListTest, HandlesEmptyPopError) {
  StackLinkedList<int> stack(10);
  EXPECT_THROW(stack.pop(), StackUnderflowError);
  stack.push(1);
  EXPECT_NO_THROW(stack.pop());
  EXPECT_THROW(stack.pop(), StackUnderflowError);
}

TEST(StackLinkedListTest, HandlesEmptyPeekError) {
  StackLinkedList<int> stack(10);
  EXPECT_THROW(stack.peek(), StackUnderflowError);
  stack.push(1);
  EXPECT_NO_THROW(stack.peek());
}

TEST(StackLinkedListTest, HandlesFullError) {
  StackLinkedList<int> stack(10);
  for (int i = 0; i < 10; i++) {
    EXPECT_NO_THROW(stack.push(i));
  }
  EXPECT_THROW(stack.push(1), StackOverflowError);
}

TEST(StackLinkedListTest, HandlesCopyConstructorStackCapacityAndSize) {
  StackLinkedList<int> s1(10);
  for (int i = 0; i < 10; i++) {
    s1.push(i);
  }
  StackLinkedList<int> s2 = s1;
  EXPECT_EQ(s1.getCapacity(), s2.getCapacity());
  EXPECT_EQ(s1.getNumberOfElements(), s2.getNumberOfElements());
}

TEST(StackLinkedListTest, HandlesClear) {
  int size = 10;
  StackLinkedList<int> s1(size);
  for (int i = 0; i < size; i++) {
    s1.push(i);
  }
  s1.clear();
  EXPECT_TRUE(s1.isEmpty());
  EXPECT_EQ(s1.getNumberOfElements(), 0);
  EXPECT_EQ(s1.getCapacity(), 0);
}

TEST(StackLinkedListTest, HandlesCopyConstructor) {
  StackLinkedList<int> s1(10);
  for (int i = 0; i < 10; i++) {
    s1.push(i);
  }
  StackLinkedList<int> s2 = s1;

  const Node<int> *n1 = s1.getTop();
  const Node<int> *n2 = s2.getTop();
  for (int i = 0; i < s1.getNumberOfElements(); i++) {
    // Memory addresses should be different
    EXPECT_NE(n1, n2);
    // Values should be same
    EXPECT_EQ(n1->value, n2->value);
    n1 = n1->next.get();
    n2 = n2->next.get();
  }

  for (int i = 0; i < 10; i++) {
    // Values should be same
    EXPECT_EQ(s1.pop(), s2.pop());
  }
}

TEST(StackLinkedListTest, HandlesCopyConstructorEmptyStack) {
  StackLinkedList<int> s1(10);
  StackLinkedList<int> s2 = s1;

  EXPECT_EQ(s1.getCapacity(), s2.getCapacity());
}

TEST(StackLinkedListTest, HandlesCopyAssignment) {
  StackLinkedList<int> s1(10);
  for (int i = 0; i < 10; i++) {
    s1.push(i);
  }
  StackLinkedList<int> s2(1);
  s2 = s1;
  EXPECT_EQ(s1.getCapacity(), s2.getCapacity());
  EXPECT_EQ(s1.getNumberOfElements(), s2.getNumberOfElements());

  const Node<int> *n1 = s1.getTop();
  const Node<int> *n2 = s2.getTop();
  for (int i = 0; i < s1.getNumberOfElements(); i++) {
    // Memory addresses should be different
    EXPECT_NE(n1, n2);
    // Values should be same
    EXPECT_EQ(n1->value, n2->value);
    n1 = n1->next.get();
    n2 = n2->next.get();
  }

  for (int i = 0; i < 10; i++) {
    // Values should be same
    EXPECT_EQ(s1.pop(), s2.pop());
  }
}

TEST(StackLinkedListTest, HandlesMoveConstructor) {
  int size = 10;
  StackLinkedList<int> s1(size);
  for (int i = 0; i < size; i++) {
    s1.push(i);
  }
  StackLinkedList<int> s2 = std::move(s1);
  EXPECT_EQ(s1.getCapacity(), 0);
  EXPECT_EQ(s1.getNumberOfElements(), 0);
  EXPECT_EQ(s1.getTop(), nullptr);
  //   EXPECT_EQ(s1.getHead(), nullptr);

  EXPECT_EQ(s2.getCapacity(), size);
  EXPECT_EQ(s2.getNumberOfElements(), size);

  for (int i = 9; i > -1; i--) {
    EXPECT_EQ(i, s2.pop());
  }
}

TEST(StackLinkedListTest, HandlesMoveAssignment) {
  int size = 10;
  StackLinkedList<int> s1(size);
  for (int i = 0; i < size; i++) {
    s1.push(i);
  }
  StackLinkedList<int> s2(1);
  s2 = std::move(s1);
  EXPECT_EQ(s1.getCapacity(), 0);
  EXPECT_EQ(s1.getNumberOfElements(), 0);
  EXPECT_EQ(s1.getTop(), nullptr);
  //   EXPECT_EQ(s1.getHead(), nullptr);

  EXPECT_EQ(s2.getCapacity(), size);
  EXPECT_EQ(s2.getNumberOfElements(), size);

  for (int i = 9; i > -1; i--) {
    EXPECT_EQ(i, s2.pop());
  }
}

#ifdef ENABLE_TIME_CONSUMING_TESTS

TEST(StackLinkedListTest, HandlesPushPopMany) {
  int capacity = INT_MAX;
  StackLinkedList<int> stack(capacity);
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
