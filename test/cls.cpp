#include <vector>
#include <iostream>

struct A {
  int k              = 12;
  std::vector<int> v = {1, 2, 3, 5};

  //A() = default;

  auto f(int x) { return x * 2; }
  int f(int x) const { return x * 2; }

  int size() const { return v.size(); }
  friend int a_friend(A const &a) { return -a.k; }

  double tpl(auto x) { return 256 + x; }

  int &operator[](int i) { return v[i]; }
  int operator[](int i) const { return v[i]; }

  int operator()(int i) { return k + i; }
  int operator()(int i, int j) const { return k + i + 10 * j; }

  bool operator==(A const &) const = default;

  int get_prop() const { return k; }
  void set_prop(int i) { k = i; }

  auto begin() const { return std::begin(v); }
  auto end() const { return std::end(v); }

  template <typename Ar> void serialize(Ar &ar, int) {
    ar & k;
    ar & v;
  }
};

std::ostream &operator<<(std::ostream &out, A const &a) { return out << "A : k = " << a.k << "\n"; }

bool operator<(A const &x, A const &y) { return x.k < y.k; }

A operator+(A const &x, A const &y) { return A{x.k + y.k}; }
A operator-(A const &x, A const &y) { return A{x.k - y.k}; }
A operator+(A const &x, int y) { return A{x.k + y}; }

// maker into a constructor
A maker_A(int i) {
  //std::cout << " I am the A maker" << std::endl;
  return A{i};
}

//void describe_operations(A a, A b, int s) {
//A{a + b};
//A{a - b};
//};
