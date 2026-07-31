"""A legacy module imported after a c2py one does not take the type away from it.

legacy_reg overwrites the entry in the legacy table, as cpp2py does, but the c2py table is
searched first, so every conversion here keeps using the c2py type.
"""

import unittest

import use_L
import c2py_a


class TestLegacyAfterC2py(unittest.TestCase):

    def test_c2py_keeps_the_type(self):
        l = use_L.make_L(3)
        self.assertIs(type(l), c2py_a.L)

        import legacy_reg
        self.assertIsNot(legacy_reg.L, c2py_a.L)  # two distinct Python types for one C++ type

        l2 = use_L.make_L(4)
        self.assertIs(type(l2), c2py_a.L)
        self.assertEqual(use_L.get_k(l2), 4)
        # not treated as a legacy holder : is_const is read from the object, a reference is wrappable
        use_L.bump(l2)
        self.assertEqual(use_L.get_k(l2), 5)
        self.assertIs(type(use_L.wrap_ref_to_L()), c2py_a.L)


if __name__ == '__main__':
    unittest.main()
