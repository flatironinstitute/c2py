import unittest
import sys

from refcount import *

class TestRefcount(unittest.TestCase):

    def test_same_refcount(self):
        x = pyobject_ptr(3.14)
        y = pyref_obj(3.14)
        self.assertEqual(sys.getrefcount(x), sys.getrefcount(y))

if __name__ == '__main__':
    unittest.main()
