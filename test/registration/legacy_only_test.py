"""L is wrapped by a module built with the legacy cpp2py, and by nobody else.

The converters must cope with a holder that has no parent and no is_const field.
"""

import unittest

import use_L
import legacy_reg


class TestLegacyHolder(unittest.TestCase):

    def test_conversion_by_value(self):
        # The by value converter allocates the legacy Python type, which owns the new L
        l = use_L.make_L(3)
        self.assertIs(type(l), legacy_reg.L)
        self.assertEqual(use_L.get_k(l), 3)

    def test_argument_by_non_const_ref(self):
        # A legacy holder always owns a mutable L : is_const must report False, and the
        # mutation must be visible on the object
        l = use_L.make_L(3)
        use_L.bump(l)
        self.assertEqual(use_L.get_k(l), 4)

    def test_wrap_a_reference_is_refused(self):
        # A legacy holder has no parent field : wrapping a reference must raise, not write
        # past the end of the object
        with self.assertRaises(TypeError) as cm:
            use_L.wrap_ref_to_L()
        self.assertIn("legacy cpp2py", str(cm.exception))

    def test_wrong_argument_type(self):
        with self.assertRaises(Exception):
            use_L.get_k(3)


if __name__ == '__main__':
    unittest.main()
