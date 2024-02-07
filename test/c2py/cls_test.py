import unittest
import numpy as np
import pickle

import cls as M

class TestIterable(unittest.TestCase):

   def test_construct(self):
        a = M.A(3)
        self.assertEqual( a.k,  3)

        a = M.A()
        self.assertEqual( a.k,  12)

   def test_meth(self):

        a = M.A(3)
        self.assertEqual(a.f(2),  4)
        self.assertEqual(M.a_friend(a),  -3)

   def test_meth_tpl(self):

        a = M.A(3)
        self.assertEqual(a.tpl(2),  258)
        self.assertEqual(a.tpl(2.5),  258.5)

   def test_properties(self):

        a = M.A(4)
        self.assertEqual(a.p,  4)
        a.p = 17
        self.assertEqual(a.k,  17)
        def f(x): 
            del x.p
        self.assertRaises(AttributeError, f, a)

   def test_iter(self):

        a = M.A(3)
        self.assertEqual([x for x in a], [1,2,3,5]) 

   def test_call_protocol(self):
        a = M.A(3)
        self.assertEqual(a(1),  4)
        self.assertEqual(a(1,2),  24)

   def test_mapping_protocol(self):
        a = M.A(3)
        self.assertEqual(len(a),  4)
        self.assertEqual(a[2], 3)
        a[2] = 10
        self.assertEqual(a[2], 10)

   def test_arithmetic(self):
        a = M.A(3)
        b = a + a
        print(b)
        self.assertEqual(b.k,  6)
        c = a + 10
        self.assertEqual(c.k, 13)
        d = c - a
        self.assertEqual(d.k, 10)
        self.assertRaises(TypeError, lambda x,y : x*y, a,b)

   def test_compare(self):
        a = M.A(3)
        b = M.A(4)
        self.assertTrue(a == a)
        self.assertTrue(a != b)
        self.assertTrue(a<b)
        self.assertRaises(NotImplementedError, lambda x,y : x>y, a,b)

   def test_print(self):
        a = M.A(4)
        self.assertEqual(str(a), "A : k = 4\n")

   def test_reduce(self):
        a = M.A(4)
        #f, t = a.__reduce__()
        #self.assertEqual( a, f(*t))
        s = pickle.dumps(a)
        a2= pickle.loads(s)
        print(a,a2)
        self.assertEqual(a, a2)

#
if __name__ == '__main__':
    unittest.main()


