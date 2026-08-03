"""Overload resolution when one of the overloads takes a type wrapped by nobody.

That overload can not convert, and the lookup that fails raises a RuntimeError. The dispatcher
tries the overloads with raise_exception false, so the error must not be left set : the next
overload would see it, and py_converter<integer>::is_convertible reads PyErr_Occurred to detect
its own failure, so it would decline as well and the whole call would fail.

Its own interpreter, as the other tests of this directory : as soon as a module registering L is
imported the lookup succeeds and there is nothing left to check.
"""

import unittest

import use_L


class TestOverloadWithAMissingType(unittest.TestCase):

    def test_int_overload_tried_first(self):
        self.assertEqual(use_L.ovl_int_first(21), 42)

    def test_int_overload_tried_second(self):
        # the L overload is tried first and declines
        self.assertEqual(use_L.ovl_L_first(21), 42)

    def test_repeated_calls(self):
        # the miss is not cached, so the failing lookup runs again on each call
        for _ in range(3):
            self.assertEqual(use_L.ovl_L_first(21), 42)

    def test_no_overload_matches(self):
        # both decline : the dispatcher reruns them raising, and reports
        with self.assertRaises(TypeError) as cm:
            use_L.ovl_L_first("not an int")
        self.assertIn("can not be converted", str(cm.exception))


if __name__ == '__main__':
    unittest.main()
