"""Two c2py modules wrapping the same C++ type."""

import unittest

import c2py_a


class TestConflictingRegistration(unittest.TestCase):

    def test_second_module(self):
        try:
            import c2py_b
        except RuntimeError as e:
            # The two modules have their own wrap_pytype<L>, as on Linux. The second registration is
            # then a different PyTypeObject for a type already in the table, and is refused :
            # add_type_object_to_main returns false, the init returns NULL, and the import raises the
            # exception it set. Nothing relies on the interpreter noticing an exception left set by an
            # init that returned its module anyway.
            self.assertIn("already registered", str(e))
            self.assertIn("c2py_a.L", str(e))
        else:
            # ... unless the two modules share one instantiation of add_type_object_to_main<L> : it is
            # a weak symbol, and dyld coalesces those across images, so on macOS the second module
            # runs the first one's code, on the first one's wrap_pytype<L>. There is then a single
            # Python type for L, both modules expose it, objects convert in both, nothing to refuse.
            self.assertIs(c2py_b.L, c2py_a.L)


if __name__ == '__main__':
    unittest.main()
