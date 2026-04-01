import unittest
import sys
import io

import deprecated_params as M

class TestDeprecatedParams(unittest.TestCase):

    def test_new_name(self):
        """Calling with the new parameter name works normally."""
        self.assertEqual(M.f_renamed(x=3, y=7), 10)
        self.assertEqual(M.f_renamed(3), 13)

    def test_old_name_warns(self):
        """Calling with the old parameter name works but prints a warning."""
        old_stderr = sys.stderr
        sys.stderr = captured = io.StringIO()
        try:
            result = M.f_renamed(old_x=5, y=2)
        finally:
            sys.stderr = old_stderr
        self.assertEqual(result, 7)
        self.assertIn("old_x", captured.getvalue())
        self.assertIn("deprecated", captured.getvalue().lower())

    def test_multiple_renames(self):
        """Multiple deprecated parameters can be renamed at once."""
        old_stderr = sys.stderr
        sys.stderr = captured = io.StringIO()
        try:
            result = M.g_renamed(old_a=3, old_b=4)
        finally:
            sys.stderr = old_stderr
        self.assertEqual(result, 12)
        self.assertIn("old_a", captured.getvalue())
        self.assertIn("old_b", captured.getvalue())

    def test_constructor_new_name(self):
        """Constructor with the new parameter name works normally."""
        obj = M.MyClass(v=42)
        self.assertEqual(obj.get_val(), 42)

    def test_constructor_old_name_warns(self):
        """Constructor with the old parameter name works but prints a warning."""
        old_stderr = sys.stderr
        sys.stderr = captured = io.StringIO()
        try:
            obj = M.MyClass(old_v=7)
        finally:
            sys.stderr = old_stderr
        self.assertEqual(obj.get_val(), 7)
        self.assertIn("old_v", captured.getvalue())
        self.assertIn("deprecated", captured.getvalue().lower())

if __name__ == '__main__':
    unittest.main()
