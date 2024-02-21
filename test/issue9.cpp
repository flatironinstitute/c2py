#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
#include <vector>
#include <iostream>
#include <functional>
#include <array>

#include <c2py/c2py.hpp>

double f(std::array<int, 3> a) { return 8; }
double g(std::array<int, 3> const &a) { return 8; }
double h(std::array<int, 3> a) { return 8; }

static_assert(c2py::concepts::IsConvertiblePy2C<std::array<int, 3> const &>);

struct dummy_class {
  template <size_t L> using myarray = std::array<double, L>;
  double do_thing(const std::function<double(const myarray<1> &)> &) { return 9; }
  //double do_thing2(const std::function<double(myarray<1>&)> f) { return 10;}
};
