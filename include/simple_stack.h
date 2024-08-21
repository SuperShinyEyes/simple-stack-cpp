#include <exception>
#include <iostream>
#include <sstream>
#include <string>

#ifndef SIMPLE_STACK_H
#define SIMPLE_STACK_H

////////////////////////////////////////////////////
// Exceptions
class StackInvalidCapacityError : public std::exception {
 public:
  StackInvalidCapacityError(const std::string &message) : message_(message) {}

  virtual const char *what() const noexcept override {
    return message_.c_str();
  }

 private:
  std::string message_;
};

class StackUnderflowError : public std::exception {
 public:
  StackUnderflowError(const std::string &message) : message_(message) {}

  virtual const char *what() const noexcept override {
    return message_.c_str();
  }

 private:
  std::string message_;
};

class StackOverflowError : public std::exception {
 public:
  StackOverflowError(const std::string &message) : message_(message) {}

  virtual const char *what() const noexcept override {
    return message_.c_str();
  }

 private:
  std::string message_;
};

////////////////////////////////////////////////////

// Stack Abstract Class
template <class T>
class Stack {
 protected:
  // These protected members should be accessible in copy/move
  // constructor/assignment.

  // During the instantiation, a user defines the maximum number items a stack
  // could hold.
  int capacity;
  int numberOfElements = 0;

 public:
  virtual bool isFull() const = 0;
  virtual bool isEmpty() const = 0;
  virtual void push(T value) = 0;
  virtual T pop() = 0;
  // virtual T peek() = 0;
  int getCapacity() const { return capacity; };
  virtual int getNumberOfElements() const = 0;
};

template <class T>
class StackList : public Stack<T> {
  T *stack;

 public:
  StackList(int capacity) {
    if (capacity < 1) {
      throw StackInvalidCapacityError(
          "Capacity must be greater than 0. You gave " +
          std::to_string(capacity));
    }
    this->capacity = capacity;
    stack = new T[capacity];
  }

  // Copy constructor
  StackList(const StackList &other) {
    this->numberOfElements = other.numberOfElements;
    this->capacity = other.capacity;
    stack = new T[this->capacity];

    for (int i = 0; i < this->capacity; i++) {
      stack[i] = other.stack[i];
    }
  }

  // Move constructor
  StackList(StackList &&other) noexcept {
    this->numberOfElements = other.numberOfElements;
    this->capacity = other.capacity;
    stack = other.stack;

    other.stack = nullptr;
    other.numberOfElements = 0;
    other.capacity = 0;
  }

  ~StackList() { delete[] stack; }

  void display() {
    std::stringstream ss;
    for (int i = 0; i < this->numberOfElements; i++) {
      ss << stack[i] << " ";
    }
    std::cout << "Stack (numberOfElements: " << this->capacity
              << "): " << (ss.str()) << std::endl;
  }

  bool isEmpty() const override { return this->getNumberOfElements() == 0; }

  bool isFull() const override {
    return this->getNumberOfElements() == this->capacity;
  }

  // Return and remove the top item
  T pop() override {
    if (isEmpty()) {
      throw StackUnderflowError("You can't pop an empty stack.");
    }
    T value = *(stack + this->numberOfElements - 1);  // FIXME: This is
    this->numberOfElements--;
    return value;
  }

  void push(T value) override {
    if (isFull()) {
      throw StackOverflowError(
          "Stack Overflow: You can't push to a full stack. The "
          "numberOfElements of the "
          "stack is " +
          std::to_string(this->capacity));
    }
    *(stack + this->numberOfElements) = value;
    this->numberOfElements++;
  }
  int getNumberOfElements() const override { return this->numberOfElements; }

  T *getStack() const { return stack; }
};

// A container of each stack item for the linked list implementation,
// `StackLinkedList`. It has an embedded "chaining" logic using `previous` and
// `next` members
template <class T>
class Node {
 public:
  T value;
  Node *next = nullptr;
  Node(T value) : value(value) {}
};

template <class T>
class StackLinkedList : public Stack<T> {
  // Holds the latest/top item in a stack.
  Node<T> *top = nullptr;

 public:
  StackLinkedList(int capacity) {
    if (capacity < 1) {
      throw StackInvalidCapacityError(
          "Capacity must be greater than 0. You gave " +
          std::to_string(capacity));
    }
    this->capacity = capacity;
  }

  // Copy constructor
  StackLinkedList(const StackLinkedList &other) {
    this->capacity = other.capacity;
    if (other.isEmpty() == true) {
      return;
    }
    // First, copy the top.
    Node<T> *otherNode = other.top;
    top = new Node<T>(otherNode->value);
    this->numberOfElements++;

    // Then, copy the remaining nodes.
    Node<T> *thisNode = top;
    otherNode = otherNode->next;
    while (otherNode != nullptr) {
      thisNode->next = new Node<T>(otherNode->value);
      thisNode = thisNode->next;
      otherNode = otherNode->next;
      this->numberOfElements++;
    }
  }

  // Copy assignment operator
  StackLinkedList &operator=(const StackLinkedList &other) {
    if (this != &other) {
      // Delete data associated with this
      deleteStack();

      // Create a temporary copy-object
      StackLinkedList temp(other);
      // Transfer ownership of the copy-object's resources to this
      // This approach minimizes the risk of memory leaks
      std::swap(this->capacity, temp.capacity);
      std::swap(this->numberOfElements, temp.numberOfElements);
      std::swap(top, temp.top);
    }
    return *this;
  }

  // Move constructor
  StackLinkedList(StackLinkedList &&other) noexcept {
    this->capacity = other.capacity;
    this->numberOfElements = other.numberOfElements;
    top = other.top;

    other.capacity = 0;
    other.numberOfElements = 0;
    other.top = nullptr;
  }

  // Move assignment operator
  StackLinkedList &operator=(StackLinkedList &&other) noexcept {
    if (this != &other) {
      deleteStack();

      std::swap(this->capacity, other.capacity);
      std::swap(this->numberOfElements, other.numberOfElements);
      std::swap(top, other.top);
    }
    return *this;
  }

  ~StackLinkedList() { deleteStack(); }

  // Empty every member of the instance. Used for move assignment/constructor
  // and destructor.
  void deleteStack() {
    while (isEmpty() == false) {
      pop();
    }
    this->capacity = 0;
  }

  // Return the number of nodes in a stack
  int getNumberOfElements() const override { return this->numberOfElements; }

  bool isEmpty() const override { return getNumberOfElements() == 0; }

  bool isFull() const override {
    return getNumberOfElements() == this->capacity;
  }

  // Return and remove the top item
  T pop() override {
    if (isEmpty()) {
      throw StackUnderflowError("You can't pop an empty stack.");
    }
    Node<T> *node = top;
    T value = node->value;
    top = top->next;
    delete node;
    this->numberOfElements--;
    return value;
  }

  void push(T value) override {
    if (isFull()) {
      throw StackOverflowError(
          "You can't push to a full stack. The numberOfElements of the stack "
          "is " +
          std::to_string(this->capacity));
    }
    Node<T> *node = new Node<T>(value);
    node->next = top;
    top = node;
    this->numberOfElements++;
  }

  Node<T> *getTop() const { return top; }
};

#endif  // SIMPLE_STACK_H
