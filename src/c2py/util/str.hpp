#pragma once
#include <sstream>
#include <functional>
#include <algorithm>
#include <map>
namespace c2py {

  // -------  reverse a std::map ---------

  template <typename K, typename V> inline constexpr auto reverse_std_map(std::map<K, V> const &m) {
    std::map<V, K> res;
    for (auto const &[k, v] : m) res.insert({v, k});
    return res;
  }

  // ------- trim a string: trim (both sides), rtrim (right only), ltrim

  inline std::string replacenl(std::string s) {
    std::replace(s.begin(), s.end(), '\n', ' ');
    return s;
  }

  const std::string whitespace_and_star = " \n\r\t\f\v";

  inline std::string trim(const std::string &s, std::string const &delim = whitespace_and_star) {
    size_t start = s.find_first_not_of(delim);
    size_t end   = s.find_last_not_of(delim);
    return (end == std::string::npos) ? "" : s.substr(start, end + 1 - start);
  }

  // -------  string join ---------

  // join the mapping of F onto the range R, with separator sep.
  // f must return a string
  template <typename It, typename F, typename Sep> std::string join(It p, It e, F f, Sep sep, bool add_last = false) {
    if (p == e) return {}; // empty R
    std::stringstream result;
    result << f(*p);
    for (++p; p != e; ++p) result << sep << f(*p);
    if (add_last) result << sep;
    return result.str();
  }

  // join the mapping of F onto the range R, with separator sep.
  // f must return a string
  template <typename R, typename F, typename Sep> std::string join(R const &r, F f, Sep sep, bool add_last = false) {
    return join(r.begin(), r.end(), f, sep, add_last);
  }

  // join with f as identity by default
  template <typename R, typename Sep> std::string join(R const &r, Sep sep, bool add_last = false) {
    return join(
       r, [](auto &&x) { return x; }, sep, add_last);
  }

} // namespace c2py
