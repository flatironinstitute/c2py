"""A type wrapped by nobody fails to convert, and the failure is not remembered.

The lookup does not cache a miss, since the module registering the type may be imported later.
"""

import unittest

import use_L


class TestNotRegistered(unittest.TestCase):

    def test_miss_then_registered(self):
        with self.assertRaises(RuntimeError) as cm:
            use_L.make_L(3)
        self.assertIn("can not be converted", str(cm.exception))

        import c2py_a
        l = use_L.make_L(3)
        self.assertIs(type(l), c2py_a.L)
        self.assertEqual(use_L.get_k(l), 3)


if __name__ == '__main__':
    unittest.main()
