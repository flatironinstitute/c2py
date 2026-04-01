#include <c2py/c2py.hpp>
#include <vector>
#include <iostream>

struct B {
  int ib = 12;
  int b(int u) { return u + 2; }
  B(int i) : ib(i) {}
};

struct A : B {
  A(int i) : B(i) {}
  int a(int i, int j) { return i + j; }
};

class C2PY_IGNORE C {
  int ic = 12;
  public:
  C(int i) : ic(i) {}
  C2PY_PROPERTY_GET(cc) int cc() const { return ic; }
};

struct D : public C {
  D(int i) : C(i) {}
};

#include "cls_der.wrap.cxx"
