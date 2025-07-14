import unittest
import numpy as np
import pickle

import bug_tpl_type as M

class TestIterable(unittest.TestCase):

   def test_A(self):
        a = M.A3()
        self.assertEqual( a.f([(1,2,3), (3,2,1)]), None)

   def test_B(self):
        b = M.Bi()
        self.assertEqual( b.f([(1,2,3), (3,2,1)]), None)

if __name__ == '__main__':
    unittest.main()


