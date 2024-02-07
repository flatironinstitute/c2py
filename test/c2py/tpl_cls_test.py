import unittest
import numpy as np
import pickle

import tpl_cls as M
AA = M.AA

class TestIterable(unittest.TestCase):

   def test_construct(self):
        a = AA(3)
        self.assertEqual( a.k,  3)
        np.testing.assert_array_equal( a.v,  [1,2,3,5])

   def test_member(self):
        a = AA()
        self.assertEqual( a.k,  12)
        a.k = 10
        self.assertEqual( a.k,  10)
        # FIXME : pb sur les const T convertion  
        #self.assertEqual( a.k_immutable,  23)
        def f(x): 
            a.k_immutable = 22
        self.assertRaises(AttributeError, f, a)

   def test_meth(self):
        a = AA(3)
        self.assertEqual(a.f(2),  4)
        self.assertEqual(a.h(2),  258)
        #self.assertEqual(M.a_friend(a),  -3)
  
#    def test_compare(self):
        # a = AA(3)
        # b = AA(4)
        # self.assertTrue(a == a)
        # self.assertTrue(a != b)
        # self.assertTrue(a<b)
        # self.assertRaises(NotImplementedError, lambda x,y : x>y, a,b)

   def test_print(self):
        a = AA(4)
        self.assertEqual(str(a), "A : k = 4\n")
  
#
if __name__ == '__main__':
    unittest.main()


