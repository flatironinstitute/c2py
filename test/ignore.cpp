#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

#include <vector>
#include <iostream>
#include <c2py/c2py.hpp>

struct a_struct {
  int a;
  C2PY_IGNORE int b  = 1;
  double x_ignore_me = 0; // should be ignored by the regex

  C2PY_IGNORE int bad_method() { return 0; }
  int method_ignore_me() { return 1; }
};
// =============== Declare module ===========================

namespace c2py_module {

  constexpr auto reject_names = ".*ignore_me";

} // namespace c2py_module
