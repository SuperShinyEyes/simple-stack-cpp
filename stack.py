from abc import ABC, abstractmethod
from typing import Optional, Tuple


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
    def copy_constructor(cls, other):
        pass

    @classmethod
    @abstractmethod
    def move_constructor(cls, other):
        pass

    @abstractmethod
    def __len__(self) -> int:
        pass

    @abstractmethod
    def __eq__(self) -> int:
        pass

    @abstractmethod
    def __str__(self) -> str:
        pass

    @abstractmethod
    def __del__(self):
        pass

    @property
    def allocated_size(self) -> int:
        return self._allocated_size

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


class StackList(Stack):
    def __init__(self, size: int):
        super().__init__(size)
        self._stack = []

    @classmethod
    def copy_constructor(cls, other: "StackList"):
        new_stack = cls(other.allocated_size)
        new_stack._stack = other._stack[:]
        return new_stack

    @classmethod
    def move_constructor(cls, other):
        new_stack = cls(other.allocated_size)
        new_stack._stack = other._stack
        other._stack = None
        return new_stack

    def __len__(self) -> int:
        return len(self._stack)

    def __eq__(self, other: "StackList") -> bool:
        return self._stack == other._stack

    def __str__(self) -> str:
        return f"Stack size: {self.allocated_size}. {self._stack}"

    def __del__(self):
        if hasattr(self, "_stack"):
            del self._stack

    def pop(self):
        super().pop()
        return self._stack.pop()

    def push(self, x):
        super().push(x)
        self._stack.append(x)


class Node(object):
    def __init__(self, x, previous: Optional["Node"] = None) -> None:
        self.value = x
        self.previous: Optional["Node"] = previous
        self.next: Optional["Node"] = None


class StackLinkedList(Stack):
    def __init__(self, size: int):
        super().__init__(size)
        self._stack: Optional["Node"] = None
        self._head: Optional["Node"] = None

    @classmethod
    def copy_constructor(cls, other: "StackLinkedList"):
        new_stack: "StackLinkedList" = cls(other.allocated_size)
        node: Optional[Node] = other._head
        while node is not None:
            new_stack.push(node.value)
            node = node.next
        return new_stack

    @classmethod
    def move_constructor(cls, other: "StackLinkedList") -> "StackLinkedList":
        new_stack: "StackLinkedList" = cls(other.allocated_size)
        node: Optional[Node] = other._head
        new_stack._head = node
        new_stack._stack = other._stack

        # Nullify the source's reference
        other._head = other._stack = None
        return new_stack

    def __len__(self) -> int:
        return len(tuple(_ for _ in self))

    def __eq__(self, other: "StackLinkedList") -> bool:
        if len(self) != len(other):
            return False

        n1: Optional[Node]
        n2: Optional[Node]
        for n1, n2 in zip(self, other):
            if n1.value != n2.value:
                return False
        else:
            return True

    def __iter__(self):
        node: Optional[Node] = self._head
        while node is not None:
            yield node
            node = node.next

    def __str__(self) -> str:
        return f"Stack size: {self.allocated_size}. {self.as_tuple}"

    def __del__(self):
        if hasattr(self, "_stack"):
            del self._stack
        if hasattr(self, "_head"):
            del self._head

    @property
    def as_tuple(self) -> Tuple:
        result = []
        node: Optional[Node] = self._head
        while node is not None:
            result.append(node.value)
            node = node.next
        return tuple(result)

    def pop(self):
        super().pop()
        value = self._stack.value
        if self._head is self._stack:
            self._head = self._stack = None
        else:
            self._stack = self._stack.previous
            self._stack.next = None

        return value

    def push(self, x):
        super().push(x)
        x = Node(x)
        if self._is_empty:
            self._head = x
        else:
            x.previous = self._stack
            self._stack.next = x
        self._stack = x
