#include <c2py/c2py.hpp>
#include <cstdint>

// Test functions for fixed-width signed types
int16_t identity_int16(int16_t x) { return x; }
int32_t identity_int32(int32_t x) { return x; }
int64_t identity_int64(int64_t x) { return x; }

// Test functions for fixed-width unsigned types
uint16_t identity_uint16(uint16_t x) { return x; }
uint32_t identity_uint32(uint32_t x) { return x; }
uint64_t identity_uint64(uint64_t x) { return x; }

// Arithmetic operation to test multi-argument conversion
int16_t add_int16(int16_t a, int16_t b) { return a + b; }

#include "integers.wrap.cxx"
