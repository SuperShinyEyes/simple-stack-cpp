#ifndef SIMPLE_STACK_H
#define SIMPLE_STACK_H

int add(int a, int b);

template <class T>
class StackList {
    int allocated_size;
    T *stack;
public:
    StackList(int size) {
        allocated_size = size;
    };
    // Return and remove the top item
    T pop();
    void push(T);
    int get_size() const {
        return allocated_size;
    }
};

#endif // SIMPLE_STACK_H
