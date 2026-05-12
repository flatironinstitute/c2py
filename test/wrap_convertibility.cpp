#include <c2py/c2py.hpp>
#include <vector>

struct A {
  int x;
  A(int x) : x{x} {}
};

class B {
  std::vector<A> data_;

  public:
  B() : data_{{1}, {2}, {3}} {}

  // C++->Python: return container of wrapped type (original bug case)
  std::vector<A> const &get_data() const { return data_; }

  // Python->C++: accept container of wrapped type
  int sum_x(std::vector<A> const &v) const {
    int s = 0;
    for (auto const &a : v) s += a.x;
    return s;
  }

  // C++->Python: return wrapped type by value
  A first() const { return data_.front(); }

  // Python->C++: accept wrapped type by value
  void push(A a) { data_.push_back(a); }
};

#include "wrap_convertibility.wrap.cxx"
