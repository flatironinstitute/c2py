import unittest

import enumcxx as M

class TestIterable(unittest.TestCase):

   def test_1(self):
        
        self.assertTrue(M.f1("a") == "a")
        self.assertTrue(M.f2("A") == "A")
        self.assertRaises(TypeError, lambda s : M.f1(s), "AA")

#
if __name__ == '__main__':
    unittest.main()


