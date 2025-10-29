#include <c2py/c2py.hpp>
#include <cstdint>
#include <limits>

// Test functions for fixed-width signed types
int8_t identity_int8(int8_t x) { return x; }
int16_t identity_int16(int16_t x) { return x; }
int32_t identity_int32(int32_t x) { return x; }
int64_t identity_int64(int64_t x) { return x; }

// Test functions for fixed-width unsigned types
uint8_t identity_uint8(uint8_t x) { return x; }
uint16_t identity_uint16(uint16_t x) { return x; }
uint32_t identity_uint32(uint32_t x) { return x; }
uint64_t identity_uint64(uint64_t x) { return x; }

// Test functions for standard types
short identity_short(short x) { return x; }
unsigned short identity_ushort(unsigned short x) { return x; }
long long identity_longlong(long long x) { return x; }

// Test function for size_t
size_t identity_size_t(size_t x) { return x; }

// Functions that return boundary values
int8_t get_int8_min() { return std::numeric_limits<int8_t>::min(); }
int8_t get_int8_max() { return std::numeric_limits<int8_t>::max(); }
uint8_t get_uint8_max() { return std::numeric_limits<uint8_t>::max(); }

int16_t get_int16_min() { return std::numeric_limits<int16_t>::min(); }
int16_t get_int16_max() { return std::numeric_limits<int16_t>::max(); }
uint16_t get_uint16_max() { return std::numeric_limits<uint16_t>::max(); }

int32_t get_int32_min() { return std::numeric_limits<int32_t>::min(); }
int32_t get_int32_max() { return std::numeric_limits<int32_t>::max(); }
uint32_t get_uint32_max() { return std::numeric_limits<uint32_t>::max(); }

int64_t get_int64_min() { return std::numeric_limits<int64_t>::min(); }
int64_t get_int64_max() { return std::numeric_limits<int64_t>::max(); }
uint64_t get_uint64_max() { return std::numeric_limits<uint64_t>::max(); }

short get_short_min() { return std::numeric_limits<short>::min(); }
short get_short_max() { return std::numeric_limits<short>::max(); }
unsigned short get_ushort_max() { return std::numeric_limits<unsigned short>::max(); }

long long get_longlong_min() { return std::numeric_limits<long long>::min(); }
long long get_longlong_max() { return std::numeric_limits<long long>::max(); }

// Arithmetic operations to test conversion
int16_t add_int16(int16_t a, int16_t b) { return a + b; }
uint32_t add_uint32(uint32_t a, uint32_t b) { return a + b; }
int64_t multiply_int64(int64_t a, int64_t b) { return a * b; }

#include "integers.wrap.cxx"
