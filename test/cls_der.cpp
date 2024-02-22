#include <vector>
#include <iostream>
#include <c2py/c2py.hpp>

struct B {
  int ib = 12;
  int b(int u) { return u + 2; }
  B(int i) : ib(i) {}
};

struct A : B {
  A(int i) : B(i) {}
  int a(int i, int j) { return i + j; }
};
