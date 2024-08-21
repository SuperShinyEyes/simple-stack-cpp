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
  //
  int size = 0;

 public:
  virtual bool isFull() const = 0;
  virtual bool isEmpty() const = 0;
  virtual void push(T value) = 0;
  virtual T pop() = 0;
  // virtual T peek() = 0;
  int getCapacity() const { return capacity; };
  virtual int getSize() const = 0;
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
    this->size = other.size;
    this->capacity = other.capacity;
    stack = new T[this->capacity];

    for (int i = 0; i < this->capacity; i++) {
      stack[i] = other.stack[i];
    }
  }

  // Move constructor
  StackList(StackList &&other) noexcept {
    this->size = other.size;
    this->capacity = other.capacity;
    stack = other.stack;

    other.stack = nullptr;
    other.size = 0;
    other.capacity = 0;
  }

  ~StackList() { delete[] stack; }

  void display() {
    std::stringstream ss;
    for (int i = 0; i < this->size; i++) {
      ss << stack[i] << " ";
    }
    std::cout << "Stack (size: " << this->capacity << "): " << (ss.str())
              << std::endl;
  }

  bool isEmpty() const override { return this->getSize() == 0; }

  bool isFull() const override { return this->getSize() == this->capacity; }

  // Return and remove the top item
  T pop() override {
    if (isEmpty()) {
      throw StackUnderflowError("You can't pop an empty stack.");
    }
    T value = *(stack + this->size - 1);  // FIXME: This is
    this->size--;
    return value;
  }

  void push(T value) override {
    if (isFull()) {
      throw StackOverflowError(
          "Stack Overflow: You can't push to a full stack. The size of the "
          "stack is " +
          std::to_string(this->capacity));
    }
    *(stack + this->size) = value;
    this->size++;
  }
  int getSize() const override { return this->size; }

  T *getStack() const { return stack; }
};

// A container of each stack item for the linked list implementation,
// `StackLinkedList`. It has an embedded "chaining" logic using `previous` and
// `next` members
template <class T>
class Node {
 public:
  T value;
  // Used to reset the "tail" during `pop`.
  Node *previous;
  // Used to traverse upon copy/move constructor/assignment
  Node *next;
  // Chain the previous and this nodes
  Node(T value, Node *previous)
      : value(value), previous(previous), next(nullptr) {
    if (previous != nullptr) {
      previous->next = this;
    }
  }
};

template <class T>
class StackLinkedList : public Stack<T> {
  // Holds the latest/top item in a stack.
  Node<T> *stack = nullptr;
  // Used for copy/move constructor/assignment.
  Node<T> *head = nullptr;

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
    Node<T> *otherNode = other.head;
    while (otherNode != nullptr) {
      push(otherNode->value);
      otherNode = otherNode->next;
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
      std::swap(this->size, temp.size);
      std::swap(head, temp.head);
      std::swap(stack, temp.stack);
    }
    return *this;
  }

  // Move constructor
  StackLinkedList(StackLinkedList &&other) noexcept {
    this->capacity = other.capacity;
    this->size = other.size;
    stack = other.stack;
    head = other.head;

    other.capacity = 0;
    other.size = 0;
    other.stack = nullptr;
    other.head = nullptr;
  }

  // Move assignment operator
  StackLinkedList &operator=(StackLinkedList &&other) noexcept {
    if (this != &other) {
      deleteStack();

      std::swap(this->capacity, other.capacity);
      std::swap(this->size, other.size);
      std::swap(head, other.head);
      std::swap(stack, other.stack);
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
  int getSize() const override { return this->size; }

  bool isEmpty() const override { return getSize() == 0; }

  bool isFull() const override { return getSize() == this->capacity; }

  // Return and remove the top item
  T pop() override {
    if (isEmpty()) {
      throw StackUnderflowError("You can't pop an empty stack.");
    }
    T value = stack->value;

    if (head == stack) {
      delete head;
      head = nullptr;
      stack = nullptr;
    } else {
      stack = stack->previous;
      delete stack->next;
      stack->next = nullptr;
    }
    this->size--;
    return value;
  }

  void push(T value) override {
    if (isFull()) {
      throw StackOverflowError(
          "You can't push to a full stack. The size of the stack is " +
          std::to_string(this->capacity));
    }
    Node<T> *node = new Node<T>(value, stack);
    if (isEmpty()) {
      head = node;
    }
    stack = node;
    this->size++;
  }

  Node<T> *getStack() const { return stack; }

  Node<T> *getHead() const { return head; }
};

#endif  // SIMPLE_STACK_H
