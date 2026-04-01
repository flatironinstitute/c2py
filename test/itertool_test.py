import unittest
import sys
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

   def test_ref_range(self):
        """Iterating over a const& vector returned by a method."""
        a = B.AClass()
        self.assertEqual(list(a.data()), [1, 2, 3, 4])
        # iterating a second time must also work (the range is a reference, not consumed)
        self.assertEqual(list(a.data()), [1, 2, 3, 4])

   def test_ref_range_guardian(self):
        """The py_range returned by data() must keep the parent object alive."""
        a = B.AClass()
        rc_before = sys.getrefcount(a)
        r = a.data()
        rc_with_range = sys.getrefcount(a)
        # the range holds a guardian reference to a
        self.assertEqual(rc_with_range, rc_before + 1)
        del r
        rc_after = sys.getrefcount(a)
        self.assertEqual(rc_after, rc_before)

if __name__ == '__main__':
    unittest.main()

