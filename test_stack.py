import unittest
from stack import *


class TestStackList(unittest.TestCase):

    def test_invalid_size_error(self):
        with self.assertRaises(StackInvalidSizeError):
            stack = StackList(0)

    def test_pop_error(self):
        stack = StackList(3)
        with self.assertRaises(StackEmptyError):
            stack.pop()

    def test_push_error(self):
        stack = StackList(3)
        with self.assertRaises(StackFullError):
            for i in range(10):
                stack.push(i)

    def test_push(self):
        stack = StackList(10)
        for i in range(10):
            stack.push(i)
            self.assertTrue(len(stack) == i + 1)

    def test_pop(self):
        stack = StackList(3)
        for i in range(3):
            stack.push(i)
        for i in range(3):
            stack.pop()
        self.assertTrue(stack._is_empty)

    def test_move_constructor(self):
        s1 = StackList(5)
        for i in range(4):
            s1.push(i)
        s2 = StackList.move_constructor(s1)

        self.assertEqual(s2._stack, [i for i in range(4)])
        self.assertIsNone(s1._stack)

    def test_copy_constructor(self):
        s1 = StackList(5)
        for i in range(4):
            s1.push(i)
        s2 = StackList.copy_constructor(s1)

        self.assertEqual(s2._stack, s1._stack)
        self.assertIsNot(s2._stack, s1._stack)


class TestStackLinkedList(unittest.TestCase):

    def test_invalid_size_error(self):
        with self.assertRaises(StackInvalidSizeError):
            stack = StackLinkedList(0)

    def test_pop_error(self):
        stack = StackLinkedList(3)
        with self.assertRaises(StackEmptyError):
            stack.pop()

    def test_length(self):
        stack = StackLinkedList(10)
        for i in range(10):
            stack.push(i)
            self.assertEqual(i + 1, len(stack))

    def test_equal(self):
        s1 = StackLinkedList(100)
        s2 = StackLinkedList(100)
        size = 10
        for i in range(size):
            s1.push(i)
            s2.push(i)

        self.assertEqual(s1, s2)

    def test_not_equal(self):
        s1 = StackLinkedList(100)
        s2 = StackLinkedList(100)
        size = 10
        for i in range(size):
            s1.push(i)

        for i in range(size - 1):
            s2.push(i)

        self.assertNotEqual(s1, s2)

    def test_push_error(self):
        stack = StackLinkedList(3)
        with self.assertRaises(StackFullError):
            for i in range(10):
                stack.push(i)

    def test_push(self):
        stack = StackLinkedList(10)
        for i in range(10):
            stack.push(i)
            self.assertTrue(len(stack) == i + 1)

    def test_pop(self):
        stack = StackLinkedList(3)
        for i in range(3):
            stack.push(i)
        for i in range(3):
            stack.pop()
        self.assertTrue(stack._is_empty)

    def test_pop_tail_next_is_none(self):
        stack = StackLinkedList(3)
        for i in range(3):
            stack.push(i)
        for i in range(3):
            self.assertIsNone(stack._stack.next)
            stack.pop()

    def test_push_content(self):
        stack = StackLinkedList(10)
        for i in range(10):
            stack.push(i)
        self.assertEqual(tuple(range(10)), stack.as_tuple)

    def test_push_pop_content(self):
        stack = StackLinkedList(100)
        result = []
        for i in range(10):
            stack.push(i)
            result.append(i)
        for i in range(5):
            stack.pop()
            result.pop()
        for i in range(10):
            stack.push(i)
            result.append(i)
        self.assertEqual(tuple(result), stack.as_tuple)

    def test_move_constructor(self):
        s1 = StackLinkedList(100)
        size = 10
        for i in range(size):
            s1.push(i)
        s2 = StackLinkedList.move_constructor(s1)

        self.assertEqual(size, len(s2))
        self.assertEqual(s2.as_tuple, tuple(range(size)))

        self.assertIsNone(s1._stack)
        self.assertIsNone(s1._head)
        self.assertEqual(0, len(s1))

    def test_copy_constructor(self):
        s1 = StackLinkedList(100)
        size = 10
        for i in range(size):
            s1.push(i)
        s2 = StackLinkedList.copy_constructor(s1)

        self.assertEqual(s1, s2)
        self.assertEqual(len(s1), len(s2))
        self.assertEqual(len(s1), size)
        self.assertIsNot(s1._stack, s2._stack)

        for n1, n2 in zip(s1, s2):
            self.assertIsNot(n1, n2)


if __name__ == "__main__":
    unittest.main()
