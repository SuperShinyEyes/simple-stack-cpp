# Simple Stack

## How to run
```terminal
# Run basic tests
> ./run.sh

# Run all tests. This may take longer than 5 minutes
> ./run.sh -a
```

## Features
- ✅ Generic implementation using class template in C++. 
- ✅ Supports push and pop operations. Pop can either return the popped value or simply remove the top item; if removing only the top item, a separate method for accessing the top object separately must also be provided. 
- ✅ Has a fixed capacity, which can be defined with a runtime value. For simplicity, the capacity can be set when the stack is created; the stack does not need to support arbitrary capacity changes after it has been initialized. 
- ✅ Supports copy construction, move construction, copy assignment, and move assignment of the stack itself. 
- All operations must have well-defined effects under all possible runtime conditions and must not trigger undefined behavior.
- 🚦All applicable errors or other edge conditions are checked and reported to the user. Errors can be reported however you see fit, e.g., using exceptions, returning error codes, etc. 
    1. `StackInvalidSizeError`
    2. `StackEmptyError`
    3. `StackFullError`
- ✅ For the stack code itself, utilities from the standard library can be used, but containers that do most of the heavy lifting for you (e.g., `std::vector`, `std::deque`, `std::list`) should not be used to implement the stack; we still want to see what you can write on your own. 
- ✅ Relevant tests should also be provided that validate stack operations work as intended and that appropriate values or errors are returned depending on runtime conditions. Test code can use any elements of the standard library or third-party libraries, including test frameworks such as GoogleTest, that may help with implementing or running tests. 
- ✅ All code should be written in C++. Any version of the standard from C++11 through C++23 can be used. 

We are interested not just in whether you can do the work, but how you do it. Attention should be given to the following
- ✅ Correctness of code, including avoidance of undefined behavior and exception safety (if applicable). 
- Clarity and readability of code, including variable and function naming, commenting where appropriate, and general coding style consistency. While there is not a specific coding style we expect you to adhere to for this task, it is recommended that you adhere to some consistent coding style or set of rules. 
- Organization of code. Please try to organize things as if this was intended to be used by end-users. 
- Clear, concise descriptions of classes, functions, member variables, etc., including parameters and return values for functions and any error conditions. Documentation comments that can be parsed by a formatted documentation generator such as Doxygen or Sphinx are strongly preferred. 
- ✅ Completeness of tests.

Please also provide information about the C++ standard version used, the compiler with which the code was tested, any build tools or other dependency requirements, and any other relevant information needed to build the code and run tests. Making it easy for us to be able to test the code on our end is strongly recommended. Most of our workstations are running either Ubuntu Linux ("Focal" or "Jammy") or Windows 11 (with Visual Studio 2022), so targeting toolchains and dependencies that are readily available on those platforms is preferred. 
You should not take much more than a few hours on this task. Do not worry if you don't feel you have enough time to address every detail mentioned here; we can go over the direction in which it would have headed given more time in a follow-up discussion. Try not to rush things, and if you do happen to finish early, try to take the extra time to polish up any details. 
 
Feel free to contact us with any questions regarding the task, and good luck!
