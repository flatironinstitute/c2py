#include <c2py/c2py.hpp>
#include <vector>
#include <iostream>

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

  // Template method with non-deducible return type
  template <typename R> R convert(auto x) { return R(x + 1); }

  // Template method with non-deducible return type and variadic pack
  template <typename R, typename... U> R call(U &&...x) { return R(sizeof...(x)); }

  bool operator==(A const &) const = default;

  int operator()(int i) const { return i + k; }

  int operator[](int i) const { return i + k; }
};

template <typename T> std::ostream &operator<<(std::ostream &out, A<T> const &a) { return out << "A : k = " << a.k << "\n"; }

template <typename T> bool operator<(A<T> const &x, A<T> const &y) { return x.k < y.k; }

template double A<int>::tpl(int);
template int A<int>::convert(double);
template double A<int>::call(long const &);

// FIXME https://godbolt.org/z/bK8rTo9Ez

// =============== Declare module ===========================

namespace c2py_module {

  using AA = A<int>;

} // namespace c2py_module

#include "tpl_cls.wrap.cxx"
