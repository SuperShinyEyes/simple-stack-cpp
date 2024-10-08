#include <exception>
#include <iostream>
#include <memory>
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

bool isValidCapacity(int capacity) { return capacity > 0; }

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
  virtual T peek() = 0;
  int getCapacity() const { return capacity; };
  virtual int getNumberOfElements() const = 0;
  virtual void clear() = 0;
};

template <class T>
class StackArray : public Stack<T> {
  std::unique_ptr<T[]> array;

 public:
  StackArray(int capacity) {
    if (!isValidCapacity(capacity)) {
      throw StackInvalidCapacityError(
          "Capacity must be greater than 0. You gave " +
          std::to_string(capacity));
    }
    this->capacity = capacity;
    array = std::make_unique<T[]>(capacity);
  }

  // Copy constructor
  StackArray(const StackArray &other) {
    this->capacity = other.capacity;
    this->numberOfElements = other.numberOfElements;
    array = std::make_unique<T[]>(this->capacity);

    for (int i = 0; i < this->numberOfElements; i++) {
      array[i] = other.array[i];
    }
  }

  // Copy assignment
  StackArray &operator=(const StackArray &other) {
    if (this != &other) {
      clear();

      // Create a temporary copy-object.
      StackArray temp = other;
      std::swap(this->capacity, temp.capacity);
      std::swap(this->numberOfElements, temp.numberOfElements);
      std::swap(this->array, temp.array);
    }
    return *this;
  }

  // Move constructor
  StackArray(StackArray &&other) noexcept {
    this->numberOfElements = other.numberOfElements;
    this->capacity = other.capacity;
    array = std::move(other.array);

    other.array = nullptr;
    other.numberOfElements = 0;
    other.capacity = 0;
  }

  // Move assignment
  StackArray &operator=(StackArray &&other) noexcept {
    if (this != &other) {
      clear();

      std::swap(this->capacity, other.capacity);
      std::swap(this->numberOfElements, other.numberOfElements);
      std::swap(this->array, other.array);
    }
    return *this;
  }

  ~StackArray() { clear(); }

  void clear() override {
    while (isEmpty() == false) {
      pop();
    }
    // delete[] array;
    array = nullptr;
    this->capacity = 0;
  }

  void display() {
    std::stringstream ss;
    for (int i = 0; i < this->numberOfElements; i++) {
      ss << array[i] << " ";
    }
    std::cout << "Stack (numberOfElements: " << this->capacity
              << "): " << (ss.str()) << std::endl;
  }

  bool isEmpty() const override { return this->getNumberOfElements() == 0; }

  bool isFull() const override {
    return this->getNumberOfElements() == this->capacity;
  }

  T peek() override {
    if (isEmpty()) {
      throw StackUnderflowError("You can't peek an empty stack.");
    }
    return array[this->numberOfElements - 1];
  }

  // Return and remove the top item
  T pop() override {
    if (isEmpty()) {
      throw StackUnderflowError("You can't pop an empty stack.");
    }
    T value = array[this->numberOfElements - 1];  // FIXME: This is
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
    array[this->numberOfElements] = value;
    this->numberOfElements++;
  }
  int getNumberOfElements() const override { return this->numberOfElements; }

  T *getArray() const { return array.get(); }
};

// A container of each stack item for the linked list implementation,
// `StackLinkedList`. It has an embedded "chaining" logic using `previous` and
// `next` members
template <class T>
class Node {
 public:
  T value;
  std::unique_ptr<Node> next;
  Node(T value) : value(value) {}
};

// Singly linked list implementation
template <class T>
class StackLinkedList : public Stack<T> {
  // Holds the latest/top item in a stack.
  std::unique_ptr<Node<T>> top;

 public:
  StackLinkedList(int capacity) {
    if (!isValidCapacity(capacity)) {
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
    Node<T> *otherNode = other.top.get();
    top = std::make_unique<Node<T>>(otherNode->value);
    this->numberOfElements++;

    // Then, copy the remaining nodes in the same sequence.
    Node<T> *thisNode = top.get();
    otherNode = otherNode->next.get();
    while (otherNode != nullptr) {
      thisNode->next = std::make_unique<Node<T>>(otherNode->value);
      thisNode = thisNode->next.get();
      otherNode = otherNode->next.get();
      this->numberOfElements++;
    }
  }

  // Copy assignment operator
  StackLinkedList &operator=(const StackLinkedList &other) {
    if (this != &other) {
      // Delete data associated with this
      clear();

      // Create a temporary copy-object
      StackLinkedList temp = other;
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
    top = std::move(other.top);

    other.capacity = 0;
    other.numberOfElements = 0;
    other.top = nullptr;
  }

  // Move assignment operator
  StackLinkedList &operator=(StackLinkedList &&other) noexcept {
    if (this != &other) {
      clear();

      std::swap(this->capacity, other.capacity);
      std::swap(this->numberOfElements, other.numberOfElements);
      std::swap(top, other.top);
    }
    return *this;
  }

  ~StackLinkedList() { clear(); }

  // Empty every member of the instance. Used for move assignment/constructor
  // and destructor.
  void clear() override {
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

  T peek() override {
    if (isEmpty()) {
      throw StackUnderflowError("You can't peek an empty stack.");
    }
    return top->value;
  }

  // Return and remove the top item
  T pop() override {
    if (isEmpty()) {
      throw StackUnderflowError("You can't pop an empty stack.");
    }
    Node<T> *node = getTop();
    T value = node->value;
    top = std::move(top->next);
    node = nullptr;
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
    std::unique_ptr<Node<T>> node = std::make_unique<Node<T>>(value);
    node->next = std::move(top);
    top = std::move(node);
    this->numberOfElements++;
  }

  Node<T> *getTop() const { return top.get(); }
};

#endif  // SIMPLE_STACK_H
