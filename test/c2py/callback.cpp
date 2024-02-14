#include <vector>
#include <iostream>
#include <c2py/c2py.hpp>

using c2py::operator"" _a;

const double precision = 1.e-9;

// Test 1 : call a simple function written in Python
void callback1() {

  PyRun_SimpleString(R"RAW(
def f(x): 
  return x*x - 2

)RAW");

  auto f = c2py::pyfunction<long>("__main__", "f");

  if (f(3) != (3 * 3 - 2)) throw std::runtime_error{"Test failed 1"};
}

// =================================================

// Test 2 : Pass a function and call it

void callback2() {

  PyRun_SimpleString(R"RAW(

def callback(f, arg):
  return f(arg)

)RAW");

  //auto callback = c2py::pyfunction<long>("__main__", "callback");
  auto callback = c2py::pyfunction<long>{"callback"};

  auto fun = std::function{[](long x) { return x * x - 2; }};
  long r   = callback(fun, 4);
  if (r != fun(4)) throw std::runtime_error{"Test failed 2"};
}

// =================================================

// Test 2 : Pass a function and call it

void callback3() {

  // Test 3 : A scipy example for the demo
  auto fun = [](double x) {
    std::cerr << "callback fun: x= " << x << "  " << x * x - 2 << std::endl;
    return x * x - 2;
  };

  if (PyRun_SimpleString("import scipy")) {
    std::cerr << "== No scipy on this machine  =====\n";
    return;
  }
  try {
    auto root_scalar = c2py::pyfunction{"scipy.optimize.root_scalar"};
    auto res         = root_scalar(fun, "x0"_a = 0, "x1"_a = 2); //
    double root      = res.attr("root").as<double>();
    if (std::abs(root - std::sqrt(2)) > precision) throw std::runtime_error{"Test scipy failed "};
  } catch (std::exception const &e) {
    std::cerr << "\n== Ended with C++ exception: =====\n" << e.what() << "\n";
    return;
  }
}
