import unittest
import numpy as np
import pickle

import ignore as M
A = M.AStruct

class TestIterable(unittest.TestCase):
 
    def test_ignore(self):
        a = A(a = 10)
        print(a.a) # ok 
        
        def f():
            A(a= 10, b =2)
        self.assertRaises(RuntimeError, f)

        def f(x): 
            print(x.b)
        self.assertRaises(AttributeError, f, a)

        def f(x): 
            print(x.x_ignore_me)
        self.assertRaises(AttributeError, f, a)

        def f(x): 
            x.bad_method(1)
        self.assertRaises(AttributeError, f, a)

        def f(x): 
            x.method_ignore_me(1)
        self.assertRaises(AttributeError, f, a)


    def test_opaque(self):
        a = M.make_opaque()
        self.assertEqual(M.take_opaque(a), 17) 
        self.assertEqual(M.inc_opaque(a), 18) 
        self.assertEqual(M.inc_opaque(a), 19) 
        self.assertEqual(M.take_opaque(a), 19) 

if __name__ == '__main__':
    unittest.main()


