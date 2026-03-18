import unittest
import sys

import accessor as M

class TestAccessor(unittest.TestCase):

    def test_const_ref(self):
        """get_a_ref returns A const&: mutation propagates back, b stays alive."""
        b = M.B()
        a_value = b.get_i(True)
        rc = sys.getrefcount(b)

        a = b.get_a_ref()
        self.assertEqual(sys.getrefcount(b), rc + 1)

        a.i *= -1
        self.assertEqual(b.get_i(True), -a_value)

        del a
        self.assertEqual(sys.getrefcount(b), rc)

    def test_nonconst_ref(self):
        """get_a_ref2 returns A&, increments a1.i before returning."""
        b = M.B()
        a_value = b.get_i(True)
        rc = sys.getrefcount(b)

        a = b.get_a_ref2()
        self.assertEqual(sys.getrefcount(b), rc + 1)

        a.i *= -1
        self.assertEqual(b.get_i(True), -(a_value + 1))

        del a
        self.assertEqual(sys.getrefcount(b), rc)

    def test_ref_switch_a1(self):
        """get_a_ref_switch(True) returns ref to a1 (i=5): mutation propagates, b stays alive."""
        b = M.B()
        rc = sys.getrefcount(b)

        a = b.get_a_ref_switch(True)
        self.assertEqual(sys.getrefcount(b), rc + 1)

        a.i *= -1
        self.assertEqual(b.get_i(True), -5)
        self.assertEqual(a.i, -5)

        del a
        self.assertEqual(sys.getrefcount(b), rc)

    def test_ref_switch_a2(self):
        """get_a_ref_switch(False) returns ref to a2 (i=10): mutation propagates, b stays alive."""
        b = M.B()
        rc = sys.getrefcount(b)

        a = b.get_a_ref_switch(False)
        self.assertEqual(sys.getrefcount(b), rc + 1)

        a.i *= -1
        self.assertEqual(b.get_i(False), -10)
        self.assertEqual(a.i, -10)

        del a
        self.assertEqual(sys.getrefcount(b), rc)

    def test_const_safety_runtime_self(self):
        """Calling a non-const method on a const-ref A must raise RuntimeError."""
        b = M.B()
        a = b.get_a_ref()
        self.assertRaises(RuntimeError, lambda x: x.m(), a)

    def test_const_safety_runtime_arg(self):
        """Passing a const-ref A to f(A&) must raise RuntimeError."""
        b = M.B()
        a = b.get_a_ref()
        self.assertRaises(RuntimeError, lambda x: M.f(x), a)

if __name__ == '__main__':
    unittest.main()
