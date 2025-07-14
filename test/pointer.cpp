#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
#include <c2py/c2py.hpp>
#include <vector>
#include <iostream>

struct a_struct {
  int a = 30;
};

int inc(a_struct *a) { return ++(a->a); }
int read(a_struct const *a) { return a->a; }

// Should not compile
// a_struct *make(a_struct *a) { return a; }
#include "pointer.wrap.cxx"
