import unittest
from stack import *


class TestCalculator(unittest.TestCase):

    def test_invalid_size_error(self):
        with self.assertRaises(StackInvalidSizeError):
            stack = Stack(0)

    def test_pop_error(self):
        stack = Stack(3)
        with self.assertRaises(StackEmptyError):
            stack.pop()

    def test_push_error(self):
        stack = Stack(3)
        with self.assertRaises(StackFullError):
            for i in range(10):
                stack.push(i)

    def test_move_constructor(self):
        s1 = Stack(5)
        for i in range(4):
            s1.push(i)
        s2 = Stack.move_constructor(s1)

        self.assertEqual(s2._stack, [i for i in range(4)])
        self.assertIsNone(s1._stack)

    def test_copy_constructor(self):
        s1 = Stack(5)
        for i in range(4):
            s1.push(i)
        s2 = Stack.copy_constructor(s1)

        self.assertEqual(s2._stack, s1._stack)
        self.assertIsNot(s2._stack, s1._stack)


if __name__ == "__main__":
    unittest.main()
