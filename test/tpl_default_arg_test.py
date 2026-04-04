import unittest

import tpl_default_arg as M


class TestTplDefaultArg(unittest.TestCase):

    def test_by_value_uses_default(self):
        self.assertEqual(M.by_value(), 0)

    def test_by_value_explicit(self):
        self.assertEqual(M.by_value(42), 42)

    def test_const_ref_uses_default(self):
        self.assertEqual(M.const_ref(), 0)

    def test_const_ref_explicit(self):
        self.assertEqual(M.const_ref(42), 42)


if __name__ == '__main__':
    unittest.main()
