import unittest
import two_module_1 as M1
import two_module_2 as M2
import numpy as np

class TestIterable(unittest.TestCase):

   def test(self):
        a = M1.A()
        b = M2.B()
        self.assertEqual(b.g(2, a), 7)

   def test_enum_class(self):
        b = M2.B()
        self.assertEqual(b.color_passthrough("Red"), "Red")
        self.assertEqual(b.color_passthrough("Blue"), "Blue")

   def test_enum(self):
        b = M2.B()
        self.assertEqual(b.direction_passthrough("North"), "North")
        self.assertEqual(b.direction_passthrough("West"), "West")

if __name__ == '__main__':
    unittest.main()

