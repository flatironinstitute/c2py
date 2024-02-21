import unittest
import itertool as B
import numpy as np

class TestIterable(unittest.TestCase):

   def test_cls(self):

        a = B.AClass()
        
        self.assertTrue(all(np.array([x for x in a.values()]) == np.array([1,4,9,16])))
        self.assertTrue(all(np.array([x for x in a.values()]) == np.array([1,4,9,16])))

   def test_fnt(self):

        r = B.trf(5)

        self.assertTrue(all(np.array([x for x in r]) == np.array([1,4,9,16,25])))
        self.assertTrue(all(np.array([x for x in r]) == np.array([1,4,9,16,25])))

if __name__ == '__main__':
    unittest.main()

