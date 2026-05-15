import unittest

import matchfile as M


class TestMatchFiles(unittest.TestCase):

    def test_aux_functions_present(self):
        self.assertEqual(M.aux_f(), 42)
        self.assertEqual(M.aux_g(5), 6)

    def test_local_function_absent(self):
        self.assertFalse(hasattr(M, 'local_f'))


if __name__ == '__main__':
    unittest.main()
