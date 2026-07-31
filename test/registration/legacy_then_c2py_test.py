"""A c2py module imported after a legacy one takes over the type.

The two tables are shared by the whole process and never emptied, so each scenario of this
directory needs its own interpreter, i.e. its own ctest entry.
"""

import unittest

import use_L


class TestLegacyThenC2py(unittest.TestCase):

    def test_c2py_takes_over(self):
        import legacy_reg
        # Only the legacy table knows L : the lookup falls back to it and reports a legacy holder
        l = use_L.make_L(3)
        self.assertIs(type(l), legacy_reg.L)
        self.assertEqual(use_L.get_k(l), 3)
        # ... so a reference can not be wrapped
        with self.assertRaises(TypeError):
            use_L.wrap_ref_to_L()

        # A c2py module wrapping L is imported now. Its registration goes in the c2py table, which
        # the lookup searches first : it must win. Nothing may have cached the legacy resolution.
        import c2py_a
        l2 = use_L.make_L(4)
        self.assertIs(type(l2), c2py_a.L)
        self.assertEqual(use_L.get_k(l2), 4)
        # ... and a reference is now wrappable
        r = use_L.wrap_ref_to_L()
        self.assertIs(type(r), c2py_a.L)
        self.assertEqual(use_L.get_k(r), 7)

        # The object made before the import is still a legacy holder, and it does not convert any
        # more : there is one entry per C++ type, and is_convertible type checks against it. Nothing
        # can be done about that, it is worth knowing.
        self.assertIs(type(l), legacy_reg.L)
        with self.assertRaises(TypeError):
            use_L.get_k(l)


if __name__ == '__main__':
    unittest.main()
