from  abc import ABC, abstractmethod
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


# Abstract Base Class
class Stack(ABC):

    def __init__(self, size: int):
        if size < 1 or not isinstance(size, int):
            raise StackInvalidSizeError(
                f"Invalid stack size argument: {size}. Should be larger than 0."
            )

        self._allocated_size = size
    
    @classmethod
    @abstractmethod
    def copy_constructor(cls, that):
        pass

    @classmethod
    @abstractmethod
    def move_constructor(cls, that):
        pass

    @property
    def allocated_size(self) -> int:
        return self._allocated_size
    
    @abstractmethod
    def __len__(self) -> int:
        pass
    
    @property
    def _is_full(self) -> bool:
        return len(self) == self._allocated_size
    
    @property
    def _is_empty(self) -> bool:
        return len(self) == 0

    @abstractmethod
    def pop(self):
        if self._is_empty:
            raise StackEmptyError("You can't pop an empty stack.")
    
    def push(self, x):
        if self._is_full:
            raise StackFullError(
                f"You can't push to a full stack. The size of the stack is {self._allocated_size}"
            )

    def __str__(self) -> str:
        return f"Stack size: {self.allocated_size}."

    @abstractmethod
    def __del__(self):
        pass


class StackList(Stack):
    def __init__(self, size: int):
        super().__init__(size)
        self._stack = []

    @classmethod
    def copy_constructor(cls, that: "StackList"):
        new_stack = cls(that.allocated_size)
        new_stack._stack = that._stack[:]
        return new_stack

    @classmethod
    def move_constructor(cls, that):
        new_stack = cls(that.allocated_size)
        new_stack._stack = that._stack
        that._stack = None
        return new_stack

    def __len__(self) -> int:
        return len(self._stack)

    def pop(self):
        super().pop()
        return self._stack.pop()
            

    def push(self, x):
        super().push(x)
        self._stack.append(x)

    def __str__(self) -> str:
        return f"Stack size: {self.allocated_size}. {self._stack}"

    def __del__(self):
        if hasattr(self, "_stack"):
            del self._stack
