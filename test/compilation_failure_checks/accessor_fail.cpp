#include <c2py/c2py.hpp>

struct A {
  int i = 10;
  A(int i) : i{i} {}
  void m() {}
};

A a_global{56};

struct B {
  A a1 = A{5};
  A &get_a_ref_global() { return a_global; }
};

#include "accessor_fail.wrap.cxx"
