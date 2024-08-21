#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "simple_stack.h"

TEST(StackListTest, HandlesConstructor) {
  StackList<int> stack(10);
  EXPECT_EQ(stack.getCapacity(), 10);
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
  for (int size : stack_sizes) {
    EXPECT_THROW(StackList<int> stack(size), StackInvalidCapacityError);
  }
}

TEST(StackListTest, HandlesValidSize) {
  std::vector<int> stack_sizes = {1000, 10, 1};
  for (int size : stack_sizes) {
    EXPECT_NO_THROW(StackList<int> stack(size));
  }
}

TEST(StackListTest, HandlesEmptyError) {
  StackList<int> stack(10);
  EXPECT_THROW(stack.pop(), StackUnderflowError);
  stack.push(1);
  EXPECT_NO_THROW(stack.pop());
  EXPECT_THROW(stack.pop(), StackUnderflowError);
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
  EXPECT_EQ(s1.getCapacity(), 0);
  EXPECT_EQ(s1.getStack(), nullptr);

  EXPECT_EQ(s2.index, size);
  EXPECT_EQ(s2.getCapacity(), size);

  for (int i = 9; i > -1; i--) {
    EXPECT_EQ(i, s2.pop());
  }
}

// LinkedList

TEST(StackLinkedListTest, HandlesConstructor) {
  StackLinkedList<int> stack(10);
  EXPECT_EQ(stack.getCapacity(), 10);
  EXPECT_EQ(stack.getSize(), 0);
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

TEST(StackLinkedListTest, HandlesInvalidSizeError) {
  std::vector<int> stack_sizes = {-1000, -10, -1, 0};
  for (int size : stack_sizes) {
    EXPECT_THROW(StackLinkedList<int> stack(size), StackInvalidCapacityError);
  }
}

TEST(StackLinkedListTest, HandlesValidSize) {
  std::vector<int> stack_sizes = {1000, 10, 1};
  for (int size : stack_sizes) {
    EXPECT_NO_THROW(StackLinkedList<int> stack(size));
  }
}

TEST(StackLinkedListTest, HandlesEmptyError) {
  StackLinkedList<int> stack(10);
  EXPECT_THROW(stack.pop(), StackUnderflowError);
  stack.push(1);
  EXPECT_NO_THROW(stack.pop());
  EXPECT_THROW(stack.pop(), StackUnderflowError);
}

TEST(StackLinkedListTest, HandlesFullError) {
  StackLinkedList<int> stack(10);
  for (int i = 0; i < 10; i++) {
    EXPECT_NO_THROW(stack.push(i));
  }
  EXPECT_THROW(stack.push(1), StackOverflowError);
}

TEST(StackLinkedListTest, HandlesCopyConstructor) {
  StackLinkedList<int> s1(10);
  for (int i = 0; i < 10; i++) {
    s1.push(i);
  }
  StackLinkedList<int> s2 = s1;
  EXPECT_EQ(s1.getCapacity(), s2.getCapacity());
  EXPECT_EQ(s1.getSize(), s2.getSize());

  const Node<int> *n1 = s1.getHead();
  const Node<int> *n2 = s2.getHead();
  for (int i = 0; i < s1.getSize(); i++) {
    // Memory addresses should be different
    EXPECT_NE(n1, n2);
    // Values should be same
    EXPECT_EQ(n1->value, n2->value);
    n1 = n1->next;
    n2 = n2->next;
  }

  for (int i = 0; i < 10; i++) {
    // Values should be same
    EXPECT_EQ(s1.pop(), s2.pop());
  }
}

TEST(StackLinkedListTest, HandlesCopyAssignment) {
  StackLinkedList<int> s1(10);
  for (int i = 0; i < 10; i++) {
    s1.push(i);
  }
  StackLinkedList<int> s2(1);
  s2 = s1;
  EXPECT_EQ(s1.getCapacity(), s2.getCapacity());
  EXPECT_EQ(s1.getSize(), s2.getSize());

  const Node<int> *n1 = s1.getHead();
  const Node<int> *n2 = s2.getHead();
  for (int i = 0; i < s1.getSize(); i++) {
    // Memory addresses should be different
    EXPECT_NE(n1, n2);
    // Values should be same
    EXPECT_EQ(n1->value, n2->value);
    n1 = n1->next;
    n2 = n2->next;
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
  EXPECT_EQ(s1.getSize(), 0);
  EXPECT_EQ(s1.getStack(), nullptr);
  EXPECT_EQ(s1.getHead(), nullptr);

  EXPECT_EQ(s2.getCapacity(), size);
  EXPECT_EQ(s2.getSize(), size);

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
  EXPECT_EQ(s1.getSize(), 0);
  EXPECT_EQ(s1.getStack(), nullptr);
  EXPECT_EQ(s1.getHead(), nullptr);

  EXPECT_EQ(s2.getCapacity(), size);
  EXPECT_EQ(s2.getSize(), size);

  for (int i = 9; i > -1; i--) {
    EXPECT_EQ(i, s2.pop());
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
