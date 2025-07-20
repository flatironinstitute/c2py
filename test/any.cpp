#include <c2py/c2py.hpp>
#include <c2py/converters/stl/any.hpp>
#include <complex>

struct opaque {
  int c                = 17; // not exposed
  int *non_convertible = 0;
  int f(int x) { return x + 1; }; // not exposed
};

// The convertion to Py is done as a PyCapsule of std::any
template <> struct c2py::py_converter<opaque> : c2py::py_converter_as_any<opaque> {};

// maker
opaque make_opaque() { return {}; }

// passing the object back from Python
int take_opaque(opaque const &x) { return x.c; }

// we can modify the object passed from Python
int inc_opaque(opaque &x) { return ++(x.c); }

#include "any.wrap.cxx"
