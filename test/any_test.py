import unittest
import numpy as np
import any as A

def is_capsule(o):
    t = type(o)
    return t.__module__ == 'builtins' and t.__name__ == 'PyCapsule'

class TestIterable(unittest.TestCase):

   def test_opaque(self):
        a = A.make_opaque()
        self.assertTrue(is_capsule(a))
        self.assertEqual(A.take_opaque(a), 17) 
        self.assertEqual(A.inc_opaque(a), 18) 
        self.assertEqual(A.inc_opaque(a), 19) 
        self.assertEqual(A.take_opaque(a), 19) 

if __name__ == '__main__':
    unittest.main()



