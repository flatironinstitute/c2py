#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

#include <c2py/c2py.hpp>
#include <vector>
#include <iostream>

struct a_struct {
  int a;
  C2PY_IGNORE int b  = 1;
  double x_ignore_me = 0; // should be ignored by the regex

  C2PY_IGNORE int bad_method() { return 0; }
  int method_ignore_me() { return 1; }
};

// example with constructor synthesis
struct opaque {
  int a  = 17;
  int *x = 0;
  [[nodiscard]] int f() const { return 2; }
};

opaque make_opaque() { return {}; }
int inc_opaque(opaque &w) { return ++w.a; }
int take_opaque(opaque const &w) { return w.a; }

// Same example, but with a constructor,
// so it does not a priori try to synthetize a constructor from a dic
// as in the previous example
struct opaque2 {
  int a  = 17;
  int *x = 0;
  [[nodiscard]] int f() const { return 2; }
  opaque2() = default;
};

opaque2 make_opaque2() { return {}; }
int inc_opaque2(opaque2 &w) { return ++w.a; }
int take_opaque2(opaque2 const &w) { return w.a; }

#include "ignore.wrap.cxx"
