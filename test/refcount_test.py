import unittest
import numpy as np
import sys

from refcount import *

class TestIterable(unittest.TestCase):

    def test_pyobject_ptr(self):
        x = pyobject_ptr(3.14)
        self.assertEqual(sys.getrefcount(x), 2)

    def test_pyref_obj(self):
        x = pyref_obj(3.14)
        self.assertEqual(sys.getrefcount(x), 2)

if __name__ == '__main__':
    unittest.main()
