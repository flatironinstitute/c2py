#pragma once

// Hand-written modules, as cls.cpp : the CPython tables and structs are declared positionally, and
// the PyCFunction casts are the ones the generated code makes.
#ifdef __clang__
#pragma clang diagnostic ignored "-Wmissing-field-initializers"
#pragma clang diagnostic ignored "-Wcast-function-type-mismatch"
#endif
#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#pragma GCC diagnostic ignored "-Wcast-function-type"
#endif

#include "c2py/c2py.hpp"

// The C++ type the modules of this directory share. What matters is that they all wrap *the same*
// type : the tables are keyed on the mangled name, so they all compete for one entry.
struct L {
  int k = 0;
};

template <> constexpr bool c2py::is_wrapped<L> = true;
