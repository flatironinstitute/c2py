import unittest
import numpy as np

import callables as C

def f(i,j): 
    return i+10*j

def f_tu(tu): 
    return tu[0]+10*tu[1]
 
class TestIterable(unittest.TestCase):

   def test_call(self):
        self.assertEqual(C.call1(f),  21)
        self.assertEqual(C.call2(f),  21)
 
   def test_make_f(self):
        ff= C.make_f()
        self.assertEqual(ff(1,2),  f(1,2))
        # send it back to C++...
        self.assertEqual(C.call1(ff),  21)

   def test_call_pair(self):
        self.assertEqual(C.call3(f_tu),  21)
        self.assertEqual(C.call4(f_tu),  21)
        self.assertEqual(C.call5(f_tu),  21)
        self.assertRaises(TypeError, lambda x : C.call3(x), f)

   def test_make_f2(self):
        ff= C.make_f2()
        self.assertEqual(ff((1,2)),  f(1,2))
        # send it back to C++...
        self.assertEqual(C.call3(ff),  21)

   def test_callback(self):
        self.assertEqual(C.callback(),  f(2,3))

if __name__ == '__main__':
    unittest.main()



