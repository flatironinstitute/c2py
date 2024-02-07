#include <vector>
#include <string>
#include <c2py/c2py.hpp>
namespace N1 {

  struct A_ndc {
    int u;
    A_ndc(int i) : u(i) {}
    bool operator==(A_ndc const &) const = default;
  };

  struct params {

    /// An int
    int i;

    /// A double
    double x = 10;

    /// A vector of int
    std::vector<int> v;

    std::vector<int> w = {1, 2, 3};

    //std::vector<int> get() { return v;}
  };

  // Same with some non default constructible members...
  struct params_ndc {

    /// An int
    int i;

    /// A double
    /// with a long doc
    double x = 10;

    /// A non default constructible object
    A_ndc ndc1;

    /// A non default constructible object with a default init
    A_ndc ndc2 = A_ndc{9};

    /// A vector of int
    std::vector<int> v;

    std::vector<int> w = {1, 2, 3};
  };

  // double pr(params const &p) { return p.x; }

} // namespace N1

// =============== Declare module ===========================

namespace c2py_module {} // namespace c2py_module
