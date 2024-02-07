#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

#include <vector>
#include <iostream>
#include <c2py/c2py.hpp>

// Test the C2PY_WRAP annotation

int f(int i) { return 1;}

C2PY_WRAP int g(int i) { return 2;}

struct C2PY_WRAP  A {
  int k                 = 12;
};

namespace c2py_module {
  // Filter all by default.
  constexpr auto reject_names = ".*";
}


