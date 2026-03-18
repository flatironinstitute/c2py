#include <c2py/c2py.hpp>

#include <string>

int f1(int const& x = 5) { return 2 + x; }
std::string f2(std::string const& s = "hello") { return s + " world"; }

#include "const_ref_default_arg.wrap.cxx"
