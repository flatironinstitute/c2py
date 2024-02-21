import unittest
import numpy as np
import pickle

import cls_der as M
A = M.A
B = M.B

class TestIterable(unittest.TestCase):

   def test_construct(self):
        a = M.A(2)
        b = M.B(3)
        self.assertEqual( a.a(1,2),  3)
        self.assertEqual( b.b(1),  3)
        self.assertEqual( a.b(1),  3)
        self.assertTrue(isinstance(a, B))
        self.assertFalse(isinstance(b, A))

#
if __name__ == '__main__':
    unittest.main()


