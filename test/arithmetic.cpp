#include <c2py/c2py.hpp>

struct A {
  int k = 0;
  A(int k) : k(k) {}
};

A operator+(A const &x, A const &y) { return A{x.k + y.k}; }
A operator-(A const &x, A const &y) { return A{x.k - y.k}; }
A operator+(A const &x, int y) { return A{x.k + y}; }

#include "arithmetic.wrap.cxx"
