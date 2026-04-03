import unittest

import config_filter as M


class TestMatchNames(unittest.TestCase):

    def test_included_symbols_present(self):
        self.assertEqual(M.included_foo(), 1)
        self.assertEqual(M.included_bar(), 2)

    def test_excluded_symbol_absent(self):
        self.assertFalse(hasattr(M, 'excluded_baz'))


if __name__ == '__main__':
    unittest.main()
