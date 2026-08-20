import unittest
import pickle

from reprser_gen import Point


class TestReprSerializationGenerated(unittest.TestCase):

    def test_repr(self):
        self.assertEqual(repr(Point(1, 2)), "Point(1, 2)")

    def test_getstate(self):
        self.assertEqual(Point(1, 2).__getstate__(), "Point(1, 2)")

    def test_pickle_roundtrip(self):
        for protocol in range(2, pickle.HIGHEST_PROTOCOL + 1):
            a = Point(3, -4)
            b = pickle.loads(pickle.dumps(a, protocol))
            self.assertEqual(a, b)
            self.assertEqual((b.x, b.y), (3, -4))


if __name__ == '__main__':
    unittest.main()
