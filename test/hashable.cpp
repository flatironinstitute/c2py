#include <c2py/c2py.hpp>
#include <functional>

namespace N {

  struct cls_hashable {
    int value = 0;

    cls_hashable() = default;
    explicit cls_hashable(int v) : value(v) {}

    bool operator==(cls_hashable const &) const = default;
  };

  struct cls_not_hashable {
    int value = 0;

    cls_not_hashable() = default;
    explicit cls_not_hashable(int v) : value(v) {}

    bool operator==(cls_not_hashable const &) const = default;
  };

} // namespace N

namespace std {
  template <> struct hash<N::cls_hashable> {
    std::size_t operator()(N::cls_hashable const &x) const noexcept { return std::hash<int>{}(x.value); }
  };
} // namespace std

#include "hashable.wrap.cxx"
