#pragma once
#include <string>

namespace c2py {
  // ===================== nv_pair ===========================
  // A simple pair name, value, with the literal operator to form it
  // "abc"_a = X  returns a nv_pair with name = "abc" and default_value = X
  //
  template <typename T> struct nv_pair {
    std::string name;
    T value;
  };

  // implement the _a operator

  struct nv_pair_builder {
    std::string name;
    template <typename T> auto operator=(T &&x) const { return nv_pair<T>{name, std::forward<T>(x)}; } //NOLINT
  };

  inline nv_pair_builder operator"" _a(const char *s, size_t) { return {s}; }
} // namespace c2py
