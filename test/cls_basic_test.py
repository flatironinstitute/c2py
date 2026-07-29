import unittest
import numpy as np
import pickle

import cls_basic as M
A = M.A
print(M.__doc__)
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
        self.assertEqual(a.m1(2),  21)
        self.assertEqual(a.h(2),  22)
        # Check friend functions are wrapped as module-level functions
        self.assertEqual(M.a_friend(a),  -3)
        self.assertEqual(M.b_friend(a),  -6)
        self.assertEqual(a.tpl(10),  266)
  
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

   def test_renamed_class_and_method(self):
        a = M.renamed_class()
        self.assertEqual(a.x, 0)
        a.renamed_method(5)
        self.assertEqual(a.x, 5)

   def test_inline_friend(self):
        b = M.B()
        # inline_friend is wrapped as a module-level function
        M.inline_friend(b)


#
class TestPythonSubclass(unittest.TestCase):
    """Python-side subclass of a wrapped C++ type passes through correctly."""

    def setUp(self):
        class B(M.A):
            pass
        self.B = B

    def test_isinstance(self):
        b = self.B(5)
        self.assertIsInstance(b, M.A)

    def test_pass_to_const_ref_function(self):
        # B instance passed to a function taking A const& and returning int
        b = self.B(3)
        self.assertEqual(M.a_friend(b), -3)

    def test_return_a_from_subclass(self):
        # operator+ takes A const& and returns A by value
        b = self.B(3)
        result = b + M.A(2)
        self.assertEqual(result.k, 5)

    def test_non_const_method_on_subclass(self):
        # non-const method — exercises is_const check on a Python subclass instance
        b = self.B(3)
        b.no_prop()  # k *= 10
        self.assertEqual(b.k, 30)

    def test_pass_to_mutating_ref_function(self):
        # B instance passed to a function taking A& (non-const) : mutation must
        # be visible on the original Python subclass instance, not on a copy.
        b = self.B(3)
        M.mutate_a(b)
        self.assertEqual(b.k, 300)

    def test_extra_python_attributes(self):
        class C(M.A):
            def __init__(self, x, label):
                super().__init__(x)
                self.label = label
        c = C(7, "hello")
        self.assertEqual(c.label, "hello")
        self.assertEqual(M.a_friend(c), -7)


if __name__ == '__main__':
    unittest.main()


