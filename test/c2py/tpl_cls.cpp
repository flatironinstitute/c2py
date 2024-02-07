#include <vector>
#include <iostream>
#include <c2py/c2py.hpp>

template <typename T> struct A {
  int k                 = 12;
  const int k_immutable = 23;
  std::vector<T> v      = {1, 2, 3, 5};

  A() = default;
  A(T i) : k(i) {}

  T f(T x) { return x * 2; }
  T f(T x) const { return x * 2; }

  int g(int x) { return x * 100; }

  double tpl(auto x) { return 256 + x; }

  bool operator==(A const &) const = default;
};

template <typename T> std::ostream &operator<<(std::ostream &out, A<T> const &a) { return out << "A : k = " << a.k << "\n"; }

template <typename T> bool operator<(A<T> const &x, A<T> const &y) { return x.k < y.k; }

// FIXME https://godbolt.org/z/bK8rTo9Ez

// =============== Declare module ===========================

// In some cases, it is necessary to explicitly instantiate
// template struct A<int>;

namespace c2py_module {

  auto get_set_as_properties = true;

  using AA = A<int>;

  template <> struct add_methods_to<A<int>> {

    static constexpr auto h = c2py::dispatch<&A<int>::tpl<int>>;
  };

} // namespace c2py_module
