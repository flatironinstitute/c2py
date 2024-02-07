import unittest
import numpy as np

from comparison import ClsEqual, ClsEqual2, ClsComp

class TestEqual(unittest.TestCase):

   def test_eq(self):

        c1 = ClsEqual()
        c2 = ClsEqual()
        c1.value = 10
        c2.value = 10
        self.assertFalse(c1 != c2)
        self.assertTrue(c1 == c2)
   
   def test_noneq(self):

        c1 = ClsEqual()
        c2 = ClsEqual()
        c1.value = 10
        c2.value = 0
        self.assertFalse(c1 == c2)
        self.assertTrue(c1 != c2)

   def test_eq(self):

        c1 = ClsEqual2()
        c2 = ClsEqual2()
        c1.value = 10
        c2.value = 10
        self.assertFalse(c1 != c2)
        self.assertTrue(c1 == c2)
   
   def test_noneq(self):

        c1 = ClsEqual2()
        c2 = ClsEqual2()
        c1.value = 10
        c2.value = 0
        self.assertFalse(c1 == c2)
        self.assertTrue(c1 != c2)

class TestComp(unittest.TestCase):

   def test_comp(self):

        c1 = ClsComp()
        c2 = ClsComp()
        c1.value = 10
        c2.value = 2
        self.assertFalse(c1 < c2)
        self.assertTrue(c1 > c2)
        #self.assertFalse(c1 <= c2)
        #self.assertTrue(c1 >= c2)
 
if __name__ == '__main__':
    unittest.main()
