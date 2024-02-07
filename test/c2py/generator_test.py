import unittest
import generator as M
import numpy as np

class TestGenerator(unittest.TestCase):

   def test_gen(self):
        g = M.enumerate_vec([1,3,4])
        self.assertEqual([(i,x) for (i,x) in g], [(0,1), (1,3), (2,4)])

if __name__ == '__main__':
    unittest.main()

