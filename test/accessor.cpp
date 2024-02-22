#include <iostream>
#include <c2py/c2py.hpp>

struct A {
  int i = 10;
  A(int i) : i{i} {}
  // A() = default;
  void m() {}
};

void f(A &a) {}

// does not compile
//void f_notwrappable(std::vector<int> & v) {} // modify a v

static_assert(!c2py::concepts::IsConvertiblePy2C<std::vector<int> &>);
static_assert(c2py::concepts::IsConvertiblePy2C<std::vector<int> const &>);

A a_global{56};

struct B {
  private:
  A a1 = A{5};
  A a2 = A{10};

  public:
  double x = 1.5;
  int get_i(bool b) const { return (b ? a1.i : a2.i); }

  A const &get_a_ref() { return a1; }

  A &get_a_ref2() {
    a1.i++;
    return a1;
  }

  A &get_a_ref_switch(bool b) {
    if (b)
      return a1;
    else
      return a2;
  }

  // Should not compile and report error on the faulty return

  // C2PY_GUARD(23) A & get_a_ref_global() { return a_global;}
  //A & get_a_ref_global() { return a_global;}
  //A & get_a_ref_switch_wrong(bool b) { if (b) return a1; else return a_global;}
};
