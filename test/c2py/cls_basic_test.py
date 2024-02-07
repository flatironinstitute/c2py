import unittest
import numpy as np
import pickle

import cls_basic as M
A = M.A

class TestIterable(unittest.TestCase):

   def test_construct(self):
        a = M.A(3)
        self.assertEqual( a.k,  3)
        np.testing.assert_array_equal( a.v,  [1,2,3,5])

   def test_clone(self):
        a = M.A(3)
        b = a.clone()
        self.assertEqual(a,b)          

   def test_member(self):
        a = M.A()
        self.assertEqual( a.k,  12)
        a.k = 10
        self.assertEqual( a.k,  10)
        # FIXME : pb sur les const T convertion  
        #self.assertEqual( a.k_immutable,  23)
        def f(x): 
            a.k_immutable = 22
        self.assertRaises(AttributeError, f, a)

   def test_properties(self):

        a = M.A(4)
        self.assertEqual(a.prop1,  4)
        a.k = 17
        self.assertEqual(a.k,  17)
        self.assertEqual(a.prop1,  17)
        def f(x): 
            del x.prop1
        self.assertRaises(AttributeError, f, a)
        a.no_prop
        self.assertEqual(a.k,  17)
        a.no_prop() # should not be prop ... 
        self.assertEqual(a.k,  170)
        print(a.no_prop)

   def test_iter(self):
        a = M.A(3)
        self.assertEqual([x for x in a], [1,2,3,5]) 

   def test_mapping_protocol(self):
        a = M.A(3)
        self.assertEqual(len(a),  4)
        self.assertEqual(a[2], 3)
        a[2] = 10
        self.assertEqual(a[2], 10)

   def test_call_protocol(self):
        a = M.A(3)
        self.assertEqual(a(1),  4)
        self.assertEqual(a(1,2),  24)

   def test_meth(self):
        a = M.A(3)
        self.assertEqual(a.f(2),  4)
        self.assertEqual(a.h(2),  22)
        # Check friend declaration are not wrapped
        self.assertFalse(hasattr(M, "a_friend"))
        #self.assertEqual(M.a_friend(a),  -3)
  
   def test_meth_with_alias(self):
        a = M.A(3)
        self.assertEqual(a.f_w_alias(2),  4)
  
   def test_static_method(self):
        self.assertEqual(A.static_method(3), -3)

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
        s = pickle.dumps(a)
        a2= pickle.loads(s)
        self.assertEqual(a, a2)

   def test_defoutside(self):
        a = M.DummyClass()
        self.assertEqual(a.do_thing(1), 3.0)

  
#
if __name__ == '__main__':
    unittest.main()


