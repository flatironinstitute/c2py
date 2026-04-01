#include <c2py/c2py.hpp>

// A function with a renamed parameter: was "old_x", now "x"
C2PY_DEPRECATED_PARAMETER_NAME(old_x : x)
int f_renamed(int x, int y = 10) { return x + y; }

// A function with multiple renamed parameters
C2PY_DEPRECATED_PARAMETER_NAME(old_a : a, old_b : b)
int g_renamed(int a, int b) { return a * b; }

// A class with a constructor that has a renamed parameter
struct MyClass {
  int val;
  C2PY_DEPRECATED_PARAMETER_NAME(old_v : v)
  MyClass(int v) : val(v) {}
  int get_val() const { return val; }
};

#include "deprecated_params.wrap.cxx"
