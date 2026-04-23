import unittest

from hashable import ClsHashable, ClsNotHashable


class TestHashable(unittest.TestCase):

    def test_hash_available(self):
        a = ClsHashable(7)
        b = ClsHashable(7)
        c = ClsHashable(8)

        # hash() returns an int and is consistent with equality
        self.assertEqual(hash(a), hash(b))
        self.assertIsInstance(hash(a), int)
        self.assertNotEqual(hash(a), hash(c))

    def test_usable_as_dict_key(self):
        d = {ClsHashable(1): "one", ClsHashable(2): "two"}
        self.assertEqual(d[ClsHashable(1)], "one")
        self.assertEqual(d[ClsHashable(2)], "two")

    def test_usable_in_set(self):
        s = {ClsHashable(5), ClsHashable(5), ClsHashable(6)}
        self.assertEqual(len(s), 2)

    def test_unhashable_still_unhashable(self):
        with self.assertRaises(TypeError):
            hash(ClsNotHashable(1))


if __name__ == "__main__":
    unittest.main()
