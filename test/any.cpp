#include <c2py/c2py.hpp>
#include <c2py/converters/stl/any.hpp>
#include <complex>

struct C2PY_OPAQUE opaque {
  int c                = 17; // not exposed
  int *non_convertible = 0;
  int f(int x) { return x + 1; }; // not exposed
};

// maker
opaque make_opaque() { return {}; }

// passing the object back from Python
int take_opaque(opaque const &x) { return x.c; }

// we can modify the object passed from Python
int inc_opaque(opaque &x) { return ++(x.c); }

// -------------------------------------
/// Same test again, with the regex

struct opaque2 {
  int c                = 17; // not exposed
  int *non_convertible = 0;
  int f(int x) { return x + 1; }; // not exposed
};

namespace NN {
  // maker
  opaque2 make_opaque2() { return {}; }

  // passing the object back from Python
  int take_opaque2(opaque2 const &x) { return x.c; }

  // we can modify the object passed from Python
  int inc_opaque2(opaque2 &x) { return ++(x.c); }
} // namespace NN
// -------------------------------------------------

namespace c2py_module {
#pragma clang diagnostic ignored "-Wunused-const-variable"

  constexpr auto opaque_match_names = ".*opaque2";

} // namespace c2py_module
