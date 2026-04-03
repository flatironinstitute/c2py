#include <c2py/c2py.hpp>

// These match match_names = "^::included_.*" and should be wrapped
int included_foo() { return 1; }
int included_bar() { return 2; }

// These do not match and should be excluded
int excluded_baz() { return 3; }

#include "config_filter.wrap.cxx"
