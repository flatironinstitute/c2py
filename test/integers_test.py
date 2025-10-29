import unittest
import numpy as np

import integers as I

class TestIntegerTypes(unittest.TestCase):

    # Test fixed-width signed types
    def test_int8(self):
        self.assertEqual(I.identity_int8(0), 0)
        self.assertEqual(I.identity_int8(127), 127)
        self.assertEqual(I.identity_int8(-128), -128)
        self.assertEqual(I.get_int8_min(), -128)
        self.assertEqual(I.get_int8_max(), 127)
        # Test overflow protection
        self.assertRaises(TypeError, I.identity_int8, 128)
        self.assertRaises(TypeError, I.identity_int8, -129)

    def test_int16(self):
        self.assertEqual(I.identity_int16(0), 0)
        self.assertEqual(I.identity_int16(32767), 32767)
        self.assertEqual(I.identity_int16(-32768), -32768)
        self.assertEqual(I.get_int16_min(), -32768)
        self.assertEqual(I.get_int16_max(), 32767)
        # Test overflow protection
        self.assertRaises(TypeError, I.identity_int16, 32768)
        self.assertRaises(TypeError, I.identity_int16, -32769)

    def test_int32(self):
        self.assertEqual(I.identity_int32(0), 0)
        self.assertEqual(I.identity_int32(2147483647), 2147483647)
        self.assertEqual(I.identity_int32(-2147483648), -2147483648)
        self.assertEqual(I.get_int32_min(), -2147483648)
        self.assertEqual(I.get_int32_max(), 2147483647)
        # Test overflow protection
        self.assertRaises(TypeError, I.identity_int32, 2147483648)
        self.assertRaises(TypeError, I.identity_int32, -2147483649)

    def test_int64(self):
        self.assertEqual(I.identity_int64(0), 0)
        self.assertEqual(I.identity_int64(9223372036854775807), 9223372036854775807)
        self.assertEqual(I.identity_int64(-9223372036854775808), -9223372036854775808)
        self.assertEqual(I.get_int64_min(), -9223372036854775808)
        self.assertEqual(I.get_int64_max(), 9223372036854775807)
        # Test overflow protection
        self.assertRaises(TypeError, I.identity_int64, 9223372036854775808)
        self.assertRaises(TypeError, I.identity_int64, -9223372036854775809)

    # Test fixed-width unsigned types
    def test_uint8(self):
        self.assertEqual(I.identity_uint8(0), 0)
        self.assertEqual(I.identity_uint8(255), 255)
        self.assertEqual(I.get_uint8_max(), 255)
        # Test overflow protection
        self.assertRaises(TypeError, I.identity_uint8, 256)
        self.assertRaises(TypeError, I.identity_uint8, -1)

    def test_uint16(self):
        self.assertEqual(I.identity_uint16(0), 0)
        self.assertEqual(I.identity_uint16(65535), 65535)
        self.assertEqual(I.get_uint16_max(), 65535)
        # Test overflow protection
        self.assertRaises(TypeError, I.identity_uint16, 65536)
        self.assertRaises(TypeError, I.identity_uint16, -1)

    def test_uint32(self):
        self.assertEqual(I.identity_uint32(0), 0)
        self.assertEqual(I.identity_uint32(4294967295), 4294967295)
        self.assertEqual(I.get_uint32_max(), 4294967295)
        # Test overflow protection
        self.assertRaises(TypeError, I.identity_uint32, 4294967296)
        self.assertRaises(TypeError, I.identity_uint32, -1)

    def test_uint64(self):
        self.assertEqual(I.identity_uint64(0), 0)
        self.assertEqual(I.identity_uint64(18446744073709551615), 18446744073709551615)
        self.assertEqual(I.get_uint64_max(), 18446744073709551615)
        # Test overflow protection
        self.assertRaises(TypeError, I.identity_uint64, 18446744073709551616)
        self.assertRaises(TypeError, I.identity_uint64, -1)

    # Test standard types
    def test_short(self):
        self.assertEqual(I.identity_short(0), 0)
        min_val = I.get_short_min()
        max_val = I.get_short_max()
        self.assertEqual(I.identity_short(min_val), min_val)
        self.assertEqual(I.identity_short(max_val), max_val)
        # Test overflow protection
        self.assertRaises(TypeError, I.identity_short, max_val + 1)
        self.assertRaises(TypeError, I.identity_short, min_val - 1)

    def test_unsigned_short(self):
        self.assertEqual(I.identity_ushort(0), 0)
        max_val = I.get_ushort_max()
        self.assertEqual(I.identity_ushort(max_val), max_val)
        # Test overflow protection
        self.assertRaises(TypeError, I.identity_ushort, max_val + 1)
        self.assertRaises(TypeError, I.identity_ushort, -1)

    def test_long_long(self):
        self.assertEqual(I.identity_longlong(0), 0)
        min_val = I.get_longlong_min()
        max_val = I.get_longlong_max()
        self.assertEqual(I.identity_longlong(min_val), min_val)
        self.assertEqual(I.identity_longlong(max_val), max_val)
        # Test overflow protection
        self.assertRaises(TypeError, I.identity_longlong, max_val + 1)
        self.assertRaises(TypeError, I.identity_longlong, min_val - 1)

    # Test size_t
    def test_size_t(self):
        self.assertEqual(I.identity_size_t(0), 0)
        self.assertEqual(I.identity_size_t(1000), 1000)
        # Test large value (should work on 64-bit systems)
        self.assertEqual(I.identity_size_t(0xFFFFFFFF), 0xFFFFFFFF)
        # Test overflow protection
        self.assertRaises(TypeError, I.identity_size_t, -1)

    # Test arithmetic operations
    def test_add_int16(self):
        self.assertEqual(I.add_int16(100, 200), 300)
        self.assertEqual(I.add_int16(-100, 50), -50)
        self.assertEqual(I.add_int16(0, 0), 0)

    def test_add_uint32(self):
        self.assertEqual(I.add_uint32(1000, 2000), 3000)
        self.assertEqual(I.add_uint32(0, 100), 100)
        self.assertEqual(I.add_uint32(0xFFFFFFFF, 0), 0xFFFFFFFF)

    def test_multiply_int64(self):
        self.assertEqual(I.multiply_int64(100, 200), 20000)
        self.assertEqual(I.multiply_int64(-100, 50), -5000)
        self.assertEqual(I.multiply_int64(0, 12345), 0)

    # Test NumPy scalar conversions
    def test_numpy_int8(self):
        val = np.int8(42)
        self.assertEqual(I.identity_int8(val), 42)

    def test_numpy_uint8(self):
        val = np.uint8(200)
        self.assertEqual(I.identity_uint8(val), 200)

    def test_numpy_uint32(self):
        val = np.uint32(12345)
        self.assertEqual(I.identity_uint32(val), 12345)

    def test_numpy_int64(self):
        val = np.int64(-999999)
        self.assertEqual(I.identity_int64(val), -999999)

    # Test NumPy scalar overflow protection
    def test_numpy_int64_to_int8_overflow(self):
        # np.int64(1000) should not fit in int8_t (range -128 to 127)
        val = np.int64(1000)
        self.assertRaises(TypeError, I.identity_int8, val)

    def test_numpy_uint32_to_uint8_overflow(self):
        # np.uint32(1000) should not fit in uint8_t (range 0 to 255)
        val = np.uint32(1000)
        self.assertRaises(TypeError, I.identity_uint8, val)

    # Test round-trip conversions
    def test_roundtrip_int16(self):
        values = [-32768, -1000, 0, 1000, 32767]
        for val in values:
            self.assertEqual(I.identity_int16(val), val)

    def test_roundtrip_uint64(self):
        values = [0, 1, 1000, 0xFFFFFFFF, 0xFFFFFFFFFFFFFFFF]
        for val in values:
            self.assertEqual(I.identity_uint64(val), val)

if __name__ == '__main__':
    unittest.main()
