#include <c2py/c2py.hpp>
#include <c2py/converters/stl/pair.hpp>
#include <c2py/converters/stl/string.hpp>
#include <functional>

// --- call ---

int call1(std::function<int(int, int)> const &f) { return f(1, 2); }

int call2(std::function<int(int, int)> f) { return f(1, 2); }

// -- make a function ----

std::function<int(int, int)> make_f() {
  return [](int i, int j) { return i + 10 * j; };
}

// --- call : more complex object ---

int call3(std::function<int(std::pair<int, int>)> const &f) { return f(std::pair{1, 2}); }

int call4(std::function<int(std::pair<int, int>)> f) { return f(std::pair{1, 2}); }

int call5(std::function<int(std::pair<int, int> const &)> f) { return f(std::pair{1, 2}); }

// -- make a function : more complex object ---

std::function<int(std::pair<int, int>)> make_f2() {
  return [](std::pair<int, int> p) { return p.first + 10 * p.second; };
}

// -- callback a function defined in python
// here in the main module
int callback() {
  // first get a pyref handle on the python function, which is defined in the test.
  auto f_py = c2py::pyref::module("__main__").attr("f");
  // convert it and call it
  auto f = c2py::py2cxx<std::function<int(int, int)>>(f_py);
  return f(2, 3);
}

// ==========  Declare the module ==========

namespace c2py_module {} // namespace c2py_module
