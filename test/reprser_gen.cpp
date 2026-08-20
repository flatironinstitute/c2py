#include <c2py/c2py.hpp>
#include <iostream>

// A class serialized through its repr : the repr is valid Python, evaluating back to an equal object.
struct Point {
  int x = 0, y = 0;

  Point() = default;
  Point(int x, int y) : x(x), y(y) {}

  bool operator==(Point const &) const = default;
};

std::ostream &operator<<(std::ostream &out, Point const &p) { return out << "Point(" << p.x << ", " << p.y << ")"; }

// The class author asserts the contract above.
template <> constexpr bool c2py::serialize_via_repr<Point> = true;

#include "reprser_gen.wrap.cxx"
