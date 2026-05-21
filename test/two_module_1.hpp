
namespace N {
  enum class Color { Red, Green, Blue };
  enum Direction { North, South, East, West };
  struct A {
    int k = 5;
    int f(int i) { return i + k; }
  };
  int f() { return 3; }
} // namespace N
