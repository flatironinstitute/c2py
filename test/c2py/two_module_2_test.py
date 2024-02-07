import unittest
import two_module_1 as M1
import two_module_2 as M2
import numpy as np

class TestIterable(unittest.TestCase):

   def test(self):
        
        a = M1.A()
        b = M2.B()
        self.assertEqual(b.g(2,a), 7)

if __name__ == '__main__':
    unittest.main()

