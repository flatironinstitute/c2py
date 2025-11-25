import unittest
import numpy as np
import integers as I

class TestIntegerTypes(unittest.TestCase):

    def test_int16_bounds(self):
        """Test small signed type with bounds checking."""
        self.assertEqual(I.identity_int16(0), 0)
        self.assertEqual(I.identity_int16(-32768), -32768)
        self.assertEqual(I.identity_int16(32767), 32767)
        self.assertRaises(TypeError, I.identity_int16, 32768)
        self.assertRaises(TypeError, I.identity_int16, -32769)

    def test_int32_bounds(self):
        """Test 32-bit signed type."""
        self.assertEqual(I.identity_int32(0), 0)
        self.assertEqual(I.identity_int32(-2147483648), -2147483648)
        self.assertEqual(I.identity_int32(2147483647), 2147483647)
        self.assertRaises(TypeError, I.identity_int32, 2147483648)
        self.assertRaises(TypeError, I.identity_int32, -2147483649)

    def test_int64_bounds(self):
        """Test 64-bit signed type (largest values)."""
        self.assertEqual(I.identity_int64(0), 0)
        self.assertEqual(I.identity_int64(-9223372036854775808), -9223372036854775808)
        self.assertEqual(I.identity_int64(9223372036854775807), 9223372036854775807)
        self.assertRaises(TypeError, I.identity_int64, 9223372036854775808)
        self.assertRaises(TypeError, I.identity_int64, -9223372036854775809)

    def test_uint16_bounds(self):
        """Test small unsigned type with negative rejection."""
        self.assertEqual(I.identity_uint16(0), 0)
        self.assertEqual(I.identity_uint16(65535), 65535)
        self.assertRaises(TypeError, I.identity_uint16, 65536)
        self.assertRaises(TypeError, I.identity_uint16, -1)

    def test_uint32_bounds(self):
        """Test 32-bit unsigned type."""
        self.assertEqual(I.identity_uint32(0), 0)
        self.assertEqual(I.identity_uint32(4294967295), 4294967295)
        self.assertRaises(TypeError, I.identity_uint32, 4294967296)
        self.assertRaises(TypeError, I.identity_uint32, -1)

    def test_uint64_bounds(self):
        """Test 64-bit unsigned type (full range)."""
        self.assertEqual(I.identity_uint64(0), 0)
        self.assertEqual(I.identity_uint64(18446744073709551615), 18446744073709551615)
        self.assertRaises(TypeError, I.identity_uint64, 18446744073709551616)
        self.assertRaises(TypeError, I.identity_uint64, -1)

    def test_numpy_scalar_conversion(self):
        """Test NumPy scalar to C++ integer conversion."""
        self.assertEqual(I.identity_int32(np.int32(42)), 42)
        self.assertEqual(I.identity_uint64(np.uint64(12345)), 12345)
        # Overflow: np.int64 value too large for int16
        self.assertRaises(TypeError, I.identity_int16, np.int64(100000))

    def test_multi_argument_function(self):
        """Test that multiple integer arguments work correctly."""
        self.assertEqual(I.add_int16(100, -50), 50)

if __name__ == '__main__':
    unittest.main()
