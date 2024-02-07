import unittest
import numpy as np

import basicfun as B

class TestIterable(unittest.TestCase):

   def test_f(self):
        self.assertEqual(B.f(2),  6)
        self.assertEqual(B.f(2, 10),  102)
        self.assertEqual(B.f(x=2, y=10),  102)
        self.assertEqual(B.f(y=10, x=2),  102)
        # Testing the protection for int overflow as f(int)-> int
        self.assertRaises(TypeError, B.f, 0x7FFFFFFF+1)
     
   def test_g(self):
        self.assertEqual(B.g(1,2),  12)
        self.assertEqual(B.g(1),  B.g(1,8))
 
   def test_h(self):
        self.assertEqual(B.h(1),  5)
        self.assertEqual(B.h(2.3),  6.3)
   
   def test_h(self):
        self.assertEqual(B.hf(1),  3)
        self.assertEqual(B.hf(2.3),  6.3)
 
   def test_w_alias(self):
        self.assertEqual(B.ret_with_alias(),  (1.3,2.0))

   def test_is_finite(self):
        self.assertTrue(B.isfinite(1 + 2j))

if __name__ == '__main__':
    unittest.main()



