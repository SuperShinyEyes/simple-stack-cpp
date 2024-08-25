# Simple Stack
This is my hobby project to learn C++ 14.

## Environment
- macOS Sonoma 14.5
- g++ version: Apple clang version 15.0.0 (clang-1500.0.40.1)

## How to run
```terminal
# Run basic tests
> ./run.sh

# Run all tests. This may take longer than 5 minutes
> ./run.sh -a
```

## Features
- 2 implementation using class template in C++. 
    1. Linear array
    2. Singly linked list
- Supported operations 
    - push
    - pop
    - peek
    - copy construction
    - move construction
    - copy assignment
    - move assignment
- User-defined & constant capacity
- 3 errors:
    1. `StackInvalidSizeError`
    2. `StackEmptyError`
    3. `StackFullError`
- Tests:
    - Large elements
    - Mixed element sizes
    - Many elements
    - Various data types

## Future work
### Concurrent Stack
- Blocking
- Non-blocking
