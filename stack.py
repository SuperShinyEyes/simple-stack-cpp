class StackError(Exception):
    def __init__(self, message):
        self.message = message
        super().__init__(self.message)


class StackInvalidSizeError(StackError):
    def __str__(self):
        return f"StackInvalidSizeError: {self.message}"


class StackEmptyError(StackError):
    def __str__(self):
        return f"StackEmptyError: {self.message}"


class StackFullError(StackError):
    def __str__(self):
        return f"StackFullError: {self.message}"


class Stack(object):
    def __init__(self, size: int):
        if size < 1 or not isinstance(size, int):
            raise StackInvalidSizeError(
                f"Invalid stack size argument: {size}. Should be larger than 0."
            )

        self._size = size
        self._stack = []

    @classmethod
    def copy_constructor(cls, that):
        new_stack = cls(that.size)
        new_stack._stack = that._stack[:]
        return new_stack

    @classmethod
    def move_constructor(cls, that):
        new_stack = cls(that.size)
        new_stack._stack = that._stack
        that._stack = None
        return new_stack

    @property
    def size(self):
        return self._size

    def _is_full(self):
        return len(self._stack) == self._size - 1

    def pop(self):
        if self._stack:
            return self._stack.pop()
        else:
            raise StackEmptyError("You can't pop an empty stack.")

    def push(self, x):
        if self._is_full():
            raise StackFullError(
                f"You can't push to a full stack. The size of the stack is {self._size}"
            )
        else:
            self._stack.append(x)

    def __str__(self) -> str:
        return f"Stack size: {self.size}. {self._stack}"

    def __del__(self):
        if hasattr(self, "_stack"):
            del self._stack
