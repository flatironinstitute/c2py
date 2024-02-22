import unittest
import numpy as np
import pickle, sys

import accessor as M
A = M.A
B = M.B

class TestAccessor(unittest.TestCase):

   def test1(self):
        b = M.B()
        a_value = b.get_i(True)
        self.assertEqual(sys.getrefcount(b), 2)

        a = b.get_a_ref()
        self.assertEqual(sys.getrefcount(b), 3)
        
        a.i *= -1
        self.assertEqual(b.get_i(True), -a_value)

        del a
        self.assertEqual(sys.getrefcount(b), 2)

   def test2(self):
        b = M.B()
        a_value = b.get_i(True)
        self.assertEqual(sys.getrefcount(b), 2)

        a = b.get_a_ref2()
        self.assertEqual(sys.getrefcount(b), 3)
        
        a.i *= -1
        self.assertEqual(b.get_i(True), -(a_value+1))

        del a
        self.assertEqual(sys.getrefcount(b), 2)
     
   def test3(self):
        b = M.B()
        
        a = b.get_a_ref_switch(True)
        a.i *= -1
        self.assertEqual(b.get_i(True), -5)
        self.assertEqual(a.i, -5)

   def test3(self):
        b = M.B()
        
        a = b.get_a_ref_switch(False)
        a.i *= -1
        self.assertEqual(b.get_i(False), -10)
        self.assertEqual(a.i, -10)

   def test_const_safety_runtime_self(self):
        b = M.B()
        a = b.get_a_ref()
        self.assertRaises(RuntimeError, lambda x : x.m(), a)

   def test_const_safety_runtime_arg(self):
        b = M.B()
        a = b.get_a_ref()
        self.assertRaises(RuntimeError, lambda x : M.f(x), a)

#
if __name__ == '__main__':
    unittest.main()


