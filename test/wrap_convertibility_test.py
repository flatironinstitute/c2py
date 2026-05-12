import unittest
import wrap_convertibility as M

class TestWrapConvertibility(unittest.TestCase):

    def test_return_container_of_wrapped(self):
        """C++->Python: method returning std::vector<A> is wrapped (original bug)."""
        b = M.B()
        self.assertEqual([a.x for a in b.get_data()], [1, 2, 3])

    def test_accept_container_of_wrapped(self):
        """Python->C++: method taking std::vector<A> is wrapped."""
        b = M.B()
        self.assertEqual(b.sum_x([M.A(10), M.A(20)]), 30)

    def test_return_wrapped_by_value(self):
        """C++->Python: method returning A by value is wrapped."""
        b = M.B()
        self.assertEqual(b.first().x, 1)

    def test_accept_wrapped_by_value(self):
        """Python->C++: method taking A by value is wrapped."""
        b = M.B()
        b.push(M.A(99))
        self.assertEqual(list(b.get_data())[-1].x, 99)

if __name__ == '__main__':
    unittest.main()
