import unittest
import properties as M


class TestMethodPropertyAnnotations(unittest.TestCase):

    def test_getter_only(self):
        a = M.A()
        self.assertEqual(a.x, 10)
        with self.assertRaises(AttributeError):
            a.x = 5  # read-only: no setter

    def test_getter_setter(self):
        a = M.A()
        self.assertAlmostEqual(a.y, 3.14)
        a.y = 2.71
        self.assertAlmostEqual(a.y, 2.71)

    def test_derived_getter(self):
        a = M.A()
        self.assertEqual(a.z, 20)  # get_z returns x_ * 2
        with self.assertRaises(AttributeError):
            a.z = 5  # read-only: no setter


class TestFreeFunctionPropertyAnnotations(unittest.TestCase):

    def test_free_getter_only(self):
        b = M.B()
        self.assertEqual(b.val, 7)
        with self.assertRaises(AttributeError):
            b.val = 3  # read-only: no setter

    def test_free_getter_setter(self):
        b = M.B()
        self.assertAlmostEqual(b.dval, 10.5)  # 7 * 1.5
        b.dval = 4.0
        self.assertEqual(b.val, 4)    # setter truncates to int
        self.assertAlmostEqual(b.dval, 6.0)  # 4 * 1.5


class TestWrapNoArgMethodsAsProperties(unittest.TestCase):

    def test_no_arg_method_is_property(self):
        """value() has no args: must be accessible as a property, not a callable."""
        c = M.C()
        self.assertEqual(c.value, 42)
        with self.assertRaises(TypeError):
            c.value()  # property returns int, which is not callable

    def test_method_with_arg_is_not_property(self):
        """add(n) has an argument: must remain a callable method."""
        c = M.C()
        self.assertEqual(c.add(8), 50)


if __name__ == '__main__':
    unittest.main()
