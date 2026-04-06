#include <c2py/c2py.hpp>

struct A {
  int k = 0;
  A(int k) : k(k) {}
};

A operator+(A const &x, A const &y) { return A{x.k + y.k}; }
A operator-(A const &x, A const &y) { return A{x.k - y.k}; }
A operator+(A const &x, int y) { return A{x.k + y}; }
A operator*(A const &x, int y) { return A{x.k * y}; }
A operator/(A const &x, int y) { return A{x.k / y}; }

// Unary minus
A operator-(A const &x) { return A{-x.k}; }

// Left shift
A &operator<<(A &x, int n) { x.k += n; return x; }

// In-place operators
A &operator+=(A &x, A const &y) { x.k += y.k; return x; }
A &operator-=(A &x, A const &y) { x.k -= y.k; return x; }
A &operator*=(A &x, int y) { x.k *= y; return x; }
A &operator/=(A &x, int y) { x.k /= y; return x; }

#include "arithmetic.wrap.cxx"
