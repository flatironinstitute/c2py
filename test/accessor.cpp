#include <c2py/c2py.hpp>

// A is a simple wrappable class with a mutable field and a non-const method.
// It is used as the referenced member type in the accessor tests.
struct A {
  int i = 10;
  A(int i) : i{i} {}
  void m() {}          // non-const: calling it on a const ref must raise RuntimeError
  int get_i() const { return i; } // const: must be callable on both const and non-const refs
};

void f(A &a) {}

// Global A: used in the compilation_failure_checks tests to verify that
// clair rejects methods returning a reference to a non-member.
A a_global{56};

// B holds two A members. Its methods return references to them, exercising
// the accessor mechanism: the returned Python object must keep B alive and
// reflect mutations back through the original reference.
class B {
  A a1 = A{5};
  A a2 = A{10};

  public:
  int get_i(bool b) const { return (b ? a1.i : a2.i); }

  // Returns a const ref: the Python wrapper must be const (no m(), no f()).
  A const &get_a_ref() { return a1; }

  // Returns a non-const ref after mutating a1 (increments i before returning).
  A &get_a_ref2() {
    a1.i++;
    return a1;
  }

  // Returns a ref to either member depending on b: tests that the correct
  // member is aliased regardless of which branch is taken.
  A &get_a_ref_switch(bool b) {
    if (b)
      return a1;
    else
      return a2;
  }

};

// Exercises the check_return_visitor fix that allows `this->member.field`.
struct Outer {
  A a;
  Outer() : a{99} {}
};

class D {
  Outer o_;

  public:
  A const &get_nested_a() const { return o_.a; }
};

#include "accessor.wrap.cxx"
