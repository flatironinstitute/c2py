#include <c2py/c2py.hpp>

// ---- Class method annotations ----

struct A {
  int x_    = 10;
  double y_ = 3.14;

  // read-only property (getter only)
  C2PY_PROPERTY_GET(x)
  int get_x() const { return x_; }

  // read-write property (getter + setter)
  C2PY_PROPERTY_GET(y)
  double get_y() const { return y_; }

  C2PY_PROPERTY_SET(y)
  void set_y(double v) { y_ = v; }

  // derived read-only property
  C2PY_PROPERTY_GET(z)
  int get_z() const { return x_ * 2; }
};

// ---- Free function annotations ----

struct B {
  int val_ = 7;
};

// read-only property via free function
C2PY_PROPERTY_GET(val)
int b_get_val(B const &b) { return b.val_; }

// read-write property via free function
C2PY_PROPERTY_GET(dval)
double b_get_dval(B const &b) { return b.val_ * 1.5; }

C2PY_PROPERTY_SET(dval)
void b_set_dval(B &b, double v) { b.val_ = static_cast<int>(v); }

// ---- wrap_no_arg_methods_as_properties option ----
// Enabled via properties.toml.  No-arg const methods become properties;
// methods with arguments remain callable.

struct C {
  int v_ = 42;

  int value() const { return v_; }  // no-arg: becomes a property
  int add(int n) const { return v_ + n; } // has arg: stays a method
};

#include "properties.wrap.cxx"
