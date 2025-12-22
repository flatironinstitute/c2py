#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

#include <c2py/c2py.hpp>
#include <vector>
#include <iostream>

struct A {
  int k                 = 12;
  const int k_immutable = 23; //NOLINT
  std::vector<int> v    = {1, 2, 3, 5};

  A() = default;
  A(int i) : k(i) {}

  auto f(int x) { return x * 2; }
  int f(int x) const { return x * 2; }

  //int const & get_k() const { return k;}

  using index_t = long;
  index_t f_w_alias(index_t i) const { return 2 * i; }

  friend int a_friend(A const &a) { return -a.k; } // should not appear

  double tpl(auto x) { return 256 + x; }

  // test having a method and a template method with same name. Was not working in v0.1
  double m1(double x) { return 19 + x; }
  template <typename T>
    requires(std::is_same_v<T, int>)
  auto m1(T x) {
    return -(19 + x);
  }

  int prop1() const { return k; }
  int prop1() { return k; }

  void no_prop() { k *= 10; }

  static int static_method(int i) { return -i; }

  //C2PY_PROPERTY("p")
  //int get_prop() const { return k; }
  //C2PY_PROPERTY_SETTER("p")
  //void set_prop(int i) { k = i; }

  int &operator[](int i) { return v[i]; }
  int operator[](int i) const { return v[i]; }
  int size() const { return v.size(); }

  int operator()(int i) { return k + i; }
  int operator()(int i, int j) const { return k + i + 10 * j; }

  auto begin() const { return std::begin(v); }
  auto end() const { return std::end(v); }

  bool operator==(A const &) const = default;

  //int const & bad() { return v[0];}

  void serialize(auto &ar) const { ar & k & v; }
  void deserialize(auto &ar) { ar & k & v; }
};

std::ostream &operator<<(std::ostream &out, A const &a) { return out << "A : k = " << a.k << "\n"; }

// Some operations
bool operator<(A const &x, A const &y) { return x.k < y.k; }
A operator+(A const &x, A const &y) { return A{x.k + y.k}; }
auto operator-(A const &x, A const &y) { return A{x.k - y.k}; }
A operator+(A const &x, int y) { return A{x.k + y}; }

// Additional method
C2PY_WRAP_AS_METHOD
C2PY_RENAME(h)
int hhh(A const &a, int j) { return j + 20; }

// Fails to compile with proper error
//struct C2PY_IGNORE ignored {};
//C2PY_WRAP_AS_METHOD int h_fail(ignored const &a, int j) { return j + 20; }
//C2PY_WRAP_AS_METHOD int h_fail2() { return 20; }

// instantiate template methods
template double A::tpl(double);
template auto A::m1(int);

// maker into a constructor
// NOT IMPLEMENT
// A maker_A(int i) {
//   std::cout << " I am the A maker" << std::endl;
//   return A{i};
// }

// To check the filter : it should not compile if hidden is filtered out
struct hidden {};
void fff(hidden h) {}

static_assert(not c2py::concepts::IsConvertibleC2Py<std::map<std::string, hidden>>);

/// test implementation outside of class

struct dummy_class {
  double do_thing(double x);
};
double dummy_class::do_thing(double x) { return 3 * x; }

template <typename T> C2PY_WRAP_AS_METHOD static T clone(T const &x) { return T{x}; };
template A clone(A const &x);

void nop(A const &a) {}

C2PY_MODULE_INIT void my_module_init() { std::cout << "===== Starting module !!=====" << std::endl; };

struct C2PY_RENAME(renamed_class) some_class {
  int x = 0;
  some_class() = default;
  C2PY_RENAME(renamed_method) void some_method(int y) { x += y; } 
};

#include "cls_basic.wrap.cxx"
