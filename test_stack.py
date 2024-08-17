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


if __name__ == "__main__":
    unittest.main()
