#include <c2py/c2py.hpp>
#include <complex>
#include <iterator>
#include <sstream>

#ifdef __clang__
#pragma clang diagnostic ignored "-Wunused-parameter"
#endif
#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

C2PY_RENAME(hf) int f1(int x) { return x * 3; }
double f1(double x) { return -x * 10; }

int f(int x) { return x * 3; }

int f(int x, int y) { return x + 10 * y; }

int f(int x);

int g(int x, int y = 8) { return x * 10 + y; }

// BUG
//int g2(int x, int y = {}) { return x;}

using return_t = double;
std::pair<return_t, double> ret_with_alias() { return std::make_pair(1.3, 2.0); }

static_assert(c2py::concepts::IsConvertibleC2Py<std::pair<return_t, double>>);

// attribute declaration must precede definition ! Cf clang message if reverse order.
C2PY_IGNORE int ignored(int x);
int ignored(int x) { return x * 3; }

using dcomplex = std::complex<double>;

namespace N {
  auto tpl(auto) { return -2; }
  template <int N> int tplxx() { return 4; }

  auto h(auto x) { return x + 4; }

  // Works only because we generate code with lambda rewriting. Taking addresses would not work (previous version)
  // left to check against backward regression.
  using std::isfinite;
  bool isfinite(dcomplex const &x) { return std::isfinite(real(x)) && std::isfinite(imag(x)); }

} // namespace N

// should fail to compile. No way to know auto ...
// template <typename T> auto square(T x); // { return x * x; }
// extern template auto square(int);

// instantiate
//template C2PY_RENAME(h) auto N::h(float x);
template C2PY_RENAME(h) auto N::h(int x);

using mylong = long;

template C2PY_RENAME(hf) auto N::h(mylong x);
template C2PY_RENAME(hf) auto N::h(double x);

//// Playing with the doc generation
/**
 * @brief A silly function to play with a vector of integers
 * 
 * @param v A vector of integers
 * @return Something new  
 */
//std::vector<int> play_with_vector(std::vector<int> v) { return v; }

/**
 * @brief A nice function to play with a vector of vectors of integers 
 * 
 * @param v  A vector of vectors of integers 
 * @return Something 
 */
//std::vector<double> play_with_vector(std::vector<std::vector<int>> v) { return {2.0, 3.0, 4.0}; }

int get_arg() { return 42; }
int dd(int x, int y = 8) { return 1; }
int dd(int x, long y = 8) { return 1; }
int dd(int x, bool y = false) { return 1; }
int dd(int x, double z, int y = get_arg()) { return 1; }
int dd(int x, std::string y = "blabla") { return 1; }

// Check two pass AST matcher.
// In one pass, it would not guarantee to see the class before the template instantiation
// Check that two passes are indeed properly implemented
template <typename T> auto zz(T const &x) { return x.y + 2; }
struct A {
  int y = 42;
  A()   = default;
};
template auto zz(A const &);

// Non-deducible template parameter: R cannot be deduced from the argument.
// The codegen must emit explicit template arguments in the lambda call.
template <typename R> R non_deducible(auto x) { return R(x + 1); }
template int non_deducible(double);
template double non_deducible(int);

// check default parameters extraction

void zfoo(int x = {}) { std::cout << x << "\n"; }
void zfoo(std::string x = {}) { std::cout << x << "\n"; }

// Forward declared function should be wrapped correctly
int zfwd_decl_fnt(int);
int zfwd_decl_fnt(int x) { return x + 1; }

#include "basicfun.wrap.cxx"
