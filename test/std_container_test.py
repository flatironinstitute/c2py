import unittest
import numpy as np

import std_container as M


class TestTuple(unittest.TestCase):

    def test_f_tuple(self):
        self.assertEqual(M.f_tuple(), (1, 2))


class TestVector(unittest.TestCase):
    # std::vector<int> converts to a numpy array

    def test_roundtrip(self):
        result = M.f_vector([1, 2, 3])
        np.testing.assert_array_equal(result, [2, 4, 6])

    def test_empty(self):
        result = M.f_vector([])
        self.assertEqual(len(result), 0)


class TestMap(unittest.TestCase):

    def test_roundtrip(self):
        result = M.f_map({"a": 1, "b": 2})
        self.assertEqual(result, {"a": 2, "b": 4})

    def test_empty(self):
        self.assertEqual(M.f_map({}), {})


class TestString(unittest.TestCase):

    def test_roundtrip(self):
        self.assertEqual(M.f_string("ab"), "abab")

    def test_empty(self):
        self.assertEqual(M.f_string(""), "")


class TestOptional(unittest.TestCase):

    def test_present(self):
        self.assertEqual(M.f_optional(True), 42)

    def test_absent(self):
        self.assertIsNone(M.f_optional(False))


if __name__ == '__main__':
    unittest.main()
