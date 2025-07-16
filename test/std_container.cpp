#include <c2py/c2py.hpp>
#include <tuple>

std::tuple<int, int> f() { return {1, 2}; }

#include "std_container.wrap.cxx"
