#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

#include "./cppcoro/generator.hpp"
#include <c2py/c2py.hpp>

static_assert(c2py::concepts::RangeOfConvertibles<cppcoro::generator<std::pair<int, int>>>);
static_assert(c2py::concepts::IsConvertibleC2Py<cppcoro::generator<std::pair<int, int>>>);

struct C2PY_IGNORE NotConvertible {};
template <> inline constexpr bool c2py::is_wrapped<NotConvertible> = false;
static_assert(not c2py::concepts::IsConvertibleC2Py<cppcoro::generator<NotConvertible>>);

// MUST take a copy. If we pass a ref, we have dangling temporary....
// Even in C++....
auto enumerate_vec(std::vector<int> v) -> cppcoro::generator<std::pair<int, decltype(v[0])>> {
  //  cppcoro::generator<std::pair<int, int>> enumerate_vec(std::vector<int> v) {

  std::cout << v[0] << std::endl;
  std::cout << v.size() << std::endl;

  //auto v = std::vector<int>{1, 2, 3, 4};
  //auto enumerate_vec(std::vector<int> const &v) -> cppcoro::generator<std::pair<int, decltype(v[0])>> {
  int n = 0;
  for (auto x : v) {
    co_yield {n, x};
    n += 1;
  }
}
