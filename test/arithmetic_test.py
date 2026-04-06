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

    def test_mul(self):
        a = M.A(4)
        b = a * 3
        self.assertEqual(b.k, 12)
        self.assertEqual(a.k, 4)  # original unchanged

    def test_div(self):
        a = M.A(12)
        b = a / 4
        self.assertEqual(b.k, 3)
        self.assertEqual(a.k, 12)  # original unchanged

    def test_neg(self):
        a = M.A(5)
        b = -a
        self.assertEqual(b.k, -5)
        # original unchanged
        self.assertEqual(a.k, 5)


    def test_lshift(self):
        a = M.A(3)
        a << 2
        self.assertEqual(a.k, 5)
        a << 3 << 2
        self.assertEqual(a.k, 10)

    def test_iadd(self):
        a = M.A(3)
        b = M.A(4)
        a += b
        self.assertEqual(a.k, 7)

    def test_isub(self):
        a = M.A(10)
        b = M.A(3)
        a -= b
        self.assertEqual(a.k, 7)

    def test_imul(self):
        a = M.A(5)
        a *= 3
        self.assertEqual(a.k, 15)

    def test_itruediv(self):
        a = M.A(12)
        a /= 4
        self.assertEqual(a.k, 3)


if __name__ == "__main__":
    unittest.main()
