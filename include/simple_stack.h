#include <exception>
#include <string>

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
    int allocated_size;
    T *stack;
public:
    int index = 0;
    StackList(int size) {
        if (size < 1) {
            throw StackInvalidSizeError("Size must be greater than 0. You gave " +std::to_string(size));
        }
        allocated_size = size;
        stack = new T[size];
    }

    ~StackList() {
        delete stack;
    }
    bool isEmpty() {
        return index == 0;
    }

    bool isFull() {
        return index == allocated_size;
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
            throw StackFullError("You can't push to a full stack. The size of the stack is " + std::to_string(allocated_size));
        }
        *(stack + index) = value;
        index++;
    }
    int get_size() const {
        return allocated_size;
    }
};

#endif // SIMPLE_STACK_H
