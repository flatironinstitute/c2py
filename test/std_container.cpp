#include <c2py/c2py.hpp>
#include <map>
#include <optional>
#include <string>
#include <tuple>
#include <vector>

std::tuple<int, int> f_tuple() { return {1, 2}; }

std::vector<int> f_vector(std::vector<int> v) {
  for (auto &x : v) x *= 2;
  return v;
}

std::map<std::string, int> f_map(std::map<std::string, int> m) {
  for (auto &[k, v] : m) v *= 2;
  return m;
}

std::string f_string(std::string s) { return s + s; }

std::optional<int> f_optional(bool present) {
  if (present) return 42;
  return std::nullopt;
}

#include "std_container.wrap.cxx"
