#include <c2py/c2py.hpp>
#include "./two_module_1.hpp"
#include "./two_module_1.wrap.hxx"

struct B {
  int g(int i, N::A const &a) { return i + a.k; }
  N::Color color_passthrough(N::Color c) { return c; }
};

#include "two_module_2.wrap.cxx"
