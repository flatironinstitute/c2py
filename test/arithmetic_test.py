import unittest
import arithmetic as M


class TestArithmetic(unittest.TestCase):
    def test_add(self):
        a = M.A(3)
        b = a + a
        self.assertEqual(b.k, 6)
        c = a + 10
        self.assertEqual(c.k, 13)

    def test_sub(self):
        a = M.A(10)
        b = M.A(3)
        self.assertEqual((a - b).k, 7)

    def test_unsupported(self):
        a = M.A(1)
        b = M.A(2)
        self.assertRaises(TypeError, lambda: a * b)
        self.assertRaises(TypeError, lambda: a / b)


if __name__ == "__main__":
    unittest.main()
