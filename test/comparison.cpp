#include <vector>
#include <iostream>
#include <c2py/c2py.hpp>

namespace N {

  struct cls_equal {

    int value = 0;

    cls_equal() = default;

    friend bool operator==(cls_equal x, cls_equal const &y) { return x.value == y.value; }
    //friend bool operator !=(cls_equal x, cls_equal const & y) { return x.value == y.value;}
  };

  struct cls_equal2 {

    int value = 0;

    cls_equal2() = default;

    bool operator==(cls_equal2 const &y) const { return value == y.value; }
  };

  struct cls_comp {

    int value = 0;

    cls_comp() = default;

    friend bool operator<(cls_comp x, cls_comp const &y) { return x.value < y.value; }
    friend bool operator>(cls_comp x, cls_comp const &y) { return x.value > y.value; }
    friend bool operator<=(cls_comp x, cls_comp const &y) { return x.value <= y.value; }
    friend bool operator>=(cls_comp x, cls_comp const &y) { return x.value >= y.value; }
  };

} // namespace N

// =============== Declare module ===========================

namespace c2py_module {} // namespace c2py_module
