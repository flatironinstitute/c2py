import unittest
import numpy as np

import std_container as M

class TestIterable(unittest.TestCase):

   def test_f(self):
        self.assertEqual(M.f(),  (1,2))

if __name__ == '__main__':
    unittest.main()



