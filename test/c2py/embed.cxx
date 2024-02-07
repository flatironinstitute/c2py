#ifdef __clang__
//#pragma clang diagnostic ignored "-W#warnings"
#endif
#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wcpp"
#endif

#include "c2py/c2py.hpp"
#include <stdexcept>

using c2py::operator"" _a;

const double precision = 1.e-9;

// No need of gtest for a single test ...
// one dependency less.
// use gtest if the tests are more complex.

int main() try {

  c2py::pyinterpreter interpret;

  interpret.exec(R"RAW(
def f(x): 
  return x*x - 2

def callback(f, arg):
  return f(arg)

)RAW");

  {
    // Test 1 : simple function
    auto f = c2py::pyfunction<long>("__main__", "f");
    if (f(3) != (3 * 3 - 2)) throw std::runtime_error{"Test failed 1"};
  }

  {
    // Test 2 : Pass a function and call it
    auto callback = c2py::pyfunction<long>("__main__", "callback");

    auto fun = std::function{[](long x) {
      // std::cout << " x= " << x << std::endl;
      return x * x - 2;
    }};
    long r   = callback(fun, 4);
    if (r != fun(4)) throw std::runtime_error{"Test failed 2"};
  }

  {
    // Test 3 : A scipy example for the demo
    auto fun = std::function<double(double)>{[](double x) {
      std::cerr << "callback fun: x= " << x << std::endl;
      return x * x - 2;
    }};

    // FIXME : merge name and module
    interpret.exec("import scipy");
    // Lead to a convertion error
    //auto root_scalar = c2py::pyfunction<double>("scipy.optimize", "root_scalar");
    auto root_scalar = c2py::pyfunction<>("scipy.optimize", "root_scalar");
    //auto root_scalar = c2py::pyfunction<>("scipy.optimize.root_scalar"); // ,;
    //auto res = root_scalar(fun);
    auto res    = root_scalar(fun, "x0"_a = 0, "x1"_a = 2); //
    double root = c2py::py2cxx<double>(res.attr("root"));

    // FIXME
    // double root = res.attr<double>("root");
    // double root = res.attr("root").as<double>();
    if (std::abs(root - std::sqrt(2)) > precision) throw std::runtime_error{"Test scipy failed "};
  }
} catch (std::exception const &e) {
  std::cerr << "\n== Ended with C++ exception: =====\n" << e.what() << "\n";
  return 1;
}
