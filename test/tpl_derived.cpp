#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

#include <vector>
#include <c2py/c2py.hpp>

namespace N {

  template <typename T> struct my_base_templated {
    my_base_templated() = default;

    // FIXME
    //T f_base_tpl(int u) { return u + 0.5; }

    using index_t = long;
    // FIXME
    //index_t get(index_t i) const { return i; }
    long get(long i) const { return i; }
  };

  struct my_base {
    int f_base(int u) { return 10 * u; }
  };

  struct my_private_base {
    void f_private_base(int u) {}
  };

  struct my_class : private my_private_base, public my_base, public my_base_templated<double> {

    int i;
    my_class() = default;
    my_class(int u) { i = u; }
  };

} // namespace N

// =============== Declare module ===========================

namespace c2py_module {

  auto reject_names = "N::my_private_base";

  // fails with error if I attempt to wrap C3 as well
  //using C3 = N::my_base_templated<double>;

} // namespace c2py_module
