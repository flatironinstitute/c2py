#include <c2py/c2py.hpp>
#include <vector>
#include <array>

struct C {};

template <int N> struct A {
  A() {}
  //static_assert(N != 3, "NO!!");
  void f([[maybe_unused]] std::vector<std::array<int, N>> v) {}
  //void g(std::array<int, N> v) {}
};

template <typename T> struct B {
  B() {}
  void f([[maybe_unused]] std::vector<std::array<T, 3>> v) {}
};

template struct A<3>;

namespace c2py_module {

  using A3 = A<3>;
  using Bi = B<int>;

} // namespace c2py_module

#include "bug_tpl_type.wrap.cxx"
