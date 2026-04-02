import namespace as M 
import unittest

class TestNamespaceFiltering(unittest.TestCase):
    def test_funcA(self):
        """Test that funcA is wrapped and callable."""
        self.assertTrue(hasattr(M, "funcA"), "funcA should be wrapped")
        M.funcA()

    def test_funcB(self):
        """Test that funcB is wrapped and callable."""
        self.assertTrue(hasattr(M, "funcB"), "funcB should be wrapped")
        M.funcB()

    def test_funcDetail(self):
        """Test that funcDetail is NOT wrapped."""
        self.assertFalse(hasattr(M, "funcDetail"), "funcDetail should NOT be wrapped")

    def test_enumE1(self):
        """Test that enum E1 is wrapped and accessible."""
        c = M.C()
        self.assertTrue(c.f1("a") == "a")
        self.assertTrue(c.f1("b") == "b")
        self.assertTrue(c.f1("c") == "c")

if __name__ == "__main__":
    unittest.main()