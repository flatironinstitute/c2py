#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
#include <c2py/c2py.hpp>

#include "./itertools/itertools.hpp"
#include <functional> // FIXME This should be automatic in the CXX

static_assert(c2py::concepts::IsConvertibleC2Py<itertools::detail::transformed<std::vector<int>, decltype([](auto &&x) { return x * x; })>>);

struct a_class {
  std::vector<int> v;
  a_class() : v{1, 2, 3, 4} {}

  [[nodiscard]] auto values() const {
    return itertools::transform(v, [](auto &&x) { return x * x; });
  }

  // Return a const reference to the vector: the py_range must keep 'self' alive via guardian
  [[nodiscard]] std::vector<int> const &data() const { return v; }
};

auto trf(int n) {
  std::vector<int> v(n);
  for (int i = 0; i < n; ++i) v[i] = i + 1;
  return itertools::transform(std::move(v), [](auto &&x) { return x * x; });
}

#include "itertool.wrap.cxx"
