import unittest
import numpy as np
import annote as M

class TestIterable(unittest.TestCase):

   def test_f(self):
        self.assertEqual(M.g(2),  2)
        self.assertFalse(hasattr(M, "f"))
     
   def test_A(self):
        self.assertEqual(M.A().k, 12)

if __name__ == '__main__':
    unittest.main()



