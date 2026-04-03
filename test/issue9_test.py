import unittest

from issue9 import f, g, h, DummyClass


class TestArrayFunctions(unittest.TestCase):

    def test_f(self):
        self.assertEqual(f([1, 2, 3]), 8.0)

    def test_g(self):
        self.assertEqual(g([1, 2, 3]), 8.0)

    def test_h(self):
        self.assertEqual(h([1, 2, 3]), 8.0)


class TestDummyClass(unittest.TestCase):

    def test_do_thing(self):
        d = DummyClass()
        result = d.do_thing(lambda x: x[0])
        self.assertEqual(result, 9.0)


if __name__ == '__main__':
    unittest.main()
