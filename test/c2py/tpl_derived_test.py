import unittest
import numpy as np

from tpl_derived import *

class TestAll(unittest.TestCase):

   def test_call(self):

        c = MyClass(3)
        self.assertEqual( c.f_base(2),  20)
        self.assertEqual( c.get(2),  2)

if __name__ == '__main__':
    unittest.main()
