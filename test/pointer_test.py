import unittest
import numpy as np
import pickle

import pointer as M
A = M.AStruct

class TestIterable(unittest.TestCase):
 
    def test_ignore(self):
        a = A(a = 10)
        print(a.a) # ok 
        self.assertEqual(M.inc(a), 11) 
        self.assertEqual(M.read(a), 11) 

if __name__ == '__main__':
    unittest.main()


