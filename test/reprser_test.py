import unittest
import pickle

import reprser as M


class TestReprSerialization(unittest.TestCase):

    def test_repr(self):
        self.assertEqual(repr(M.R(3)), "R(3)")

    def test_getstate(self):
        self.assertEqual(M.R(7).__getstate__(), "R(7)")

    def test_pickle_roundtrip(self):
        for protocol in range(2, pickle.HIGHEST_PROTOCOL + 1):
            a = M.R(42)
            b = pickle.loads(pickle.dumps(a, protocol))
            self.assertEqual(a, b)
            self.assertEqual(b.k, 42)

    def test_setstate_bad_state(self):
        a = M.R.__new__(M.R)
        with self.assertRaises(TypeError):
            a.__setstate__(12)

    def test_setstate_bad_repr(self):
        a = M.R.__new__(M.R)
        with self.assertRaises(NameError):
            a.__setstate__("not_a_name_in_this_module(3)")

    def test_setstate_unimportable_module(self):
        a = M.BadModule.__new__(M.BadModule)
        with self.assertRaises(ImportError):
            a.__setstate__("BadModule(1)")

    def test_setstate_no_module_in_tp_name(self):
        a = M.NoModule.__new__(M.NoModule)
        with self.assertRaises(RuntimeError):
            a.__setstate__("NoModule(1)")


if __name__ == '__main__':
    unittest.main()
