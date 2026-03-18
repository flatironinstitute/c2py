#include <c2py/c2py.hpp>
#include <complex>

C2PY_RENAME(hf) int f1(int x) { return x * 3; }
double f1(double x) { return -x * 10; }

/** 
 * A doc for f(x)
 * 
 * @param x The doc of x
 */
int f(int x) { return x * 3; }

/** 
 * A doc for f(x,y)
 * 
 * @param x The doc of x
 * @param y The doc of y
 */
int f(int x, int y) { return x + 10 * y; }

int f(int x);

int g(int x, int y = 8) { return x * 10 + y; }

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


using mylong= long;

template C2PY_RENAME(hf) auto N::h(mylong x);
template C2PY_RENAME(hf) auto N::h(double x);



int ff1(int x) { return x + 2; }
int f2(int x) { return x + 2; }
int f3(int x) { return x + 2; }
int f4(int x) { return x + 2; }
int f5(int x) { return x + 2; }
int f6(int x) { return x + 2; }
int f7(int x) { return x + 2; }
int f8(int x) { return x + 2; }
int f9(int x) { return x + 2; }
int f10(int x) { return x + 2; }
int f11(int x) { return x + 2; }
int f12(int x) { return x + 2; }
int f13(int x) { return x + 2; }
int f14(int x) { return x + 2; }
int f15(int x) { return x + 2; }
int f16(int x) { return x + 2; }
int f17(int x) { return x + 2; }
int f18(int x) { return x + 2; }
int f19(int x) { return x + 2; }
int f20(int x) { return x + 2; }
int f21(int x) { return x + 2; }
int f22(int x) { return x + 2; }
int f23(int x) { return x + 2; }
int f24(int x) { return x + 2; }
int f25(int x) { return x + 2; }
int f26(int x) { return x + 2; }
int f27(int x) { return x + 2; }
int f28(int x) { return x + 2; }
int f29(int x) { return x + 2; }
int f30(int x) { return x + 2; }
int f31(int x) { return x + 2; }
int f32(int x) { return x + 2; }
int f33(int x) { return x + 2; }
int f34(int x) { return x + 2; }
int f35(int x) { return x + 2; }
int f36(int x) { return x + 2; }
int f37(int x) { return x + 2; }
int f38(int x) { return x + 2; }
int f39(int x) { return x + 2; }
int f40(int x) { return x + 2; }
int f41(int x) { return x + 2; }
int f42(int x) { return x + 2; }
int f43(int x) { return x + 2; }
int f44(int x) { return x + 2; }
int f45(int x) { return x + 2; }
int f46(int x) { return x + 2; }
int f47(int x) { return x + 2; }
int f48(int x) { return x + 2; }
int f49(int x) { return x + 2; }
int f50(int x) { return x + 2; }
int f51(int x) { return x + 2; }
int f52(int x) { return x + 2; }
int f53(int x) { return x + 2; }
int f54(int x) { return x + 2; }
int f55(int x) { return x + 2; }
int f56(int x) { return x + 2; }
int f57(int x) { return x + 2; }
int f58(int x) { return x + 2; }
int f59(int x) { return x + 2; }
int f60(int x) { return x + 2; }
int f61(int x) { return x + 2; }
int f62(int x) { return x + 2; }
int f63(int x) { return x + 2; }
int f64(int x) { return x + 2; }
int f65(int x) { return x + 2; }
int f66(int x) { return x + 2; }
int f67(int x) { return x + 2; }
int f68(int x) { return x + 2; }
int f69(int x) { return x + 2; }
int f70(int x) { return x + 2; }
int f71(int x) { return x + 2; }
int f72(int x) { return x + 2; }
int f73(int x) { return x + 2; }
int f74(int x) { return x + 2; }
int f75(int x) { return x + 2; }
int f76(int x) { return x + 2; }
int f77(int x) { return x + 2; }
int f78(int x) { return x + 2; }
int f79(int x) { return x + 2; }
int f80(int x) { return x + 2; }
int f81(int x) { return x + 2; }
int f82(int x) { return x + 2; }
int f83(int x) { return x + 2; }
int f84(int x) { return x + 2; }
int f85(int x) { return x + 2; }
int f86(int x) { return x + 2; }
int f87(int x) { return x + 2; }
int f88(int x) { return x + 2; }
int f89(int x) { return x + 2; }
int f90(int x) { return x + 2; }
int f91(int x) { return x + 2; }
int f92(int x) { return x + 2; }
int f93(int x) { return x + 2; }
int f94(int x) { return x + 2; }
int f95(int x) { return x + 2; }
int f96(int x) { return x + 2; }
int f97(int x) { return x + 2; }
int f98(int x) { return x + 2; }
int f99(int x) { return x + 2; }
int f100(int x) { return x + 2; }



#include "basicfun.wrap.cxx"
