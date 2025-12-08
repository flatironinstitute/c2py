import unittest

from const_ref_default_arg import *

class TestConstRefDefaultArg(unittest.TestCase):

    def test_f1(self):
        self.assertEqual(f1(), 7)
        self.assertEqual(f1(10), 12)

    def test_f2(self):
        self.assertEqual(f2(), "hello world")
        self.assertEqual(f2("hi"), "hi world")

if __name__ == '__main__':
    unittest.main()
