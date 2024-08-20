#include <exception>
#include <string>
#include <iostream>
#include <sstream>

#ifndef SIMPLE_STACK_H
#define SIMPLE_STACK_H

int add(int a, int b);

class StackInvalidSizeError : public std::exception {
public:
    StackInvalidSizeError(const std::string& message) : message_(message) {}

    virtual const char* what() const noexcept override {
        return message_.c_str();
    }

private:
    std::string message_;
};

class StackEmptyError : public std::exception {
public:
    StackEmptyError(const std::string& message) : message_(message) {}

    virtual const char* what() const noexcept override {
        return message_.c_str();
    }

private:
    std::string message_;
};

class StackFullError : public std::exception {
public:
    StackFullError(const std::string& message) : message_(message) {}

    virtual const char* what() const noexcept override {
        return message_.c_str();
    }

private:
    std::string message_;
};

template <class T>
class StackList {
    int allocatedSize;
    T *stack;
public:
    int index = 0;
    StackList(int size) {
        if (size < 1) {
            throw StackInvalidSizeError("Size must be greater than 0. You gave " +std::to_string(size));
        }
        allocatedSize = size;
        stack = new T[size];
    }

    // Copy constructor
    StackList(const StackList &other) {
        index = other.index;
        allocatedSize = other.allocatedSize;
        stack = new T[allocatedSize];

        for (int i = 0; i < allocatedSize; i++) {
            stack[i] = other.stack[i];
        }
    }

    StackList(StackList &&other) noexcept {
        index = other.index;
        allocatedSize = other.allocatedSize;
        stack = other.stack;
        
        other.stack = nullptr;
        other.index = 0;
        other.allocatedSize = 0;
    }

    ~StackList() {
        delete[] stack;
    }

    void display() {
        std::stringstream ss;
        for (int i = 0; i < index; i++) {
            ss << stack[i] << " ";
        }
        std::cout << "Stack (size: " << allocatedSize << "): " << (ss.str()) << std::endl;
    }

    bool isEmpty() {
        return index == 0;
    }

    bool isFull() {
        return index == allocatedSize;
    }

    // Return and remove the top item
    T pop(){
        if (isEmpty()) {
            throw StackEmptyError("You can't pop an empty stack.");
        }
        T value = *(stack + index - 1); // FIXME: This is 
        index--;
        return value;
    }

    void push(T value) {
        if (isFull()) {
            throw StackFullError("You can't push to a full stack. The size of the stack is " + std::to_string(allocatedSize));
        }
        *(stack + index) = value;
        index++;
    }
    int getSize() const {
        return allocatedSize;
    }

    T* getStack() const {
        return stack;
    }
};

template <class T>
class Node {
public:
    T value;
    Node *previous;
    Node *next;
    Node(T value, Node *previous) : value(value), previous(previous), next(nullptr) {
        if (previous != nullptr) {
            previous->next = this;
        }
    }
};

template <class T>
class StackLinkedList {
    int allocatedSize;
    Node<T> *stack;
    Node<T> *head;
public:
    StackLinkedList(int size) {
        if (size < 1) {
            throw StackInvalidSizeError("Size must be greater than 0. You gave " +std::to_string(size));
        }
        allocatedSize = size;
        stack = nullptr;
        head = nullptr;
    }

    // Copy constructor
    StackLinkedList(const StackLinkedList &other) {
        allocatedSize = other.allocatedSize;
        if (other.head == nullptr) {
            stack = nullptr;
            head = nullptr;
        } else {
            head = new Node<T>(other.head->value, nullptr);
            stack = head;
            Node<T> *node = other.head->next;
            while (node != nullptr) {
                stack = new Node<T>(node->value, stack);
                node = node->next;
            }   
        }
    }

    // Move constructor
    StackLinkedList(StackLinkedList &&other) noexcept {
        allocatedSize = other.allocatedSize;
        stack = other.stack;
        head = other.head;

        other.stack = nullptr;
        other.head = nullptr;
        other.allocatedSize = 0;
    }

    ~StackLinkedList() {
        Node<T> *n1 = head;
        Node<T> *n2 = head;
        while (n1 != nullptr) {
            n2 = n1->next;
            delete n1;
            n1 = n2;
        }
    }

    // Return the number of nodes in a stack
    int getLength() {
        int size = 0;
        Node<T> *node = head;
        while (size < allocatedSize) {
            if (node == nullptr) {
                break;
            }
            node = node->next;
            size++;
        }
        return size;
    }

    int getSize() {
        return allocatedSize;
    }

    bool isEmpty() {
        return head == nullptr;
    }

    bool isFull() {
        return getLength() == allocatedSize;
    }

    // Return and remove the top item
    T pop(){
        if (isEmpty()) {
            throw StackEmptyError("You can't pop an empty stack.");
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
        return value;
    }

    void push(T value) {
        if (isFull()) {
            throw StackFullError("You can't push to a full stack. The size of the stack is " + std::to_string(allocatedSize));
        }
        Node<T> *node = new Node<T>(value, stack);
        if (isEmpty()) {
            head = node;
        }
        stack = node;
    }

    T* getStack() const {
        return stack;
    }
};

#endif // SIMPLE_STACK_H
