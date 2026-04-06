import unittest

import tpl_pack as M


class TestTemplateParameterPacks(unittest.TestCase):

    def test_deduced_after_pack_int(self):
        self.assertEqual(M.deduced_after_pack(10), 10)

    def test_deduced_after_pack_double(self):
        self.assertAlmostEqual(M.deduced_after_pack(2.5), 2.5)

    def test_fn_param_pack_empty(self):
        self.assertEqual(M.fn_param_pack(10), 10)

    def test_fn_param_pack_one_arg(self):
        self.assertEqual(M.fn_param_pack(10, 3.14), 11)

    def test_fn_param_pack_two_args(self):
        self.assertEqual(M.fn_param_pack(10, 3.14, 'a'), 12)


if __name__ == '__main__':
    unittest.main()
