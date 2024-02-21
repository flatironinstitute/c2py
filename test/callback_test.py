import unittest
import numpy as np

import callback as M

class TestCallback(unittest.TestCase):

   def test_callback1(self):
        M.callback1()

   def test_callback2(self):
        M.callback2()
 
   def test_callback3(self):
        M.callback3()
 
if __name__ == '__main__':
    unittest.main()
