#ifndef SIMPLE_STACK_H
#define SIMPLE_STACK_H

int add(int a, int b);

template <class T>
class StackList {
    int allocated_size;
    T *stack;
public:
    int index = 0;
    StackList(int size) {
        allocated_size = size;
        stack = new T[size];
    }

    ~StackList() {
        delete stack;
    }
    bool isEmpty() {
        return index == 0;
    }

    // Return and remove the top item
    T pop(){
        T value = *(stack + index - 1); // FIXME: This is 
        index--;
        return value;
    }

    void push(T value) {
        *(stack + index) = value;
        index++;
    }
    int get_size() const {
        return allocated_size;
    }
};

#endif // SIMPLE_STACK_H
