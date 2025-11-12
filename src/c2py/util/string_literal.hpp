#pragma once
#include <array>
#include <string>
#include <array>
#include <concepts>
#include <iostream>

namespace c2py {

  // constexpr_sstream
  template <size_t N> struct constexpr_sstream {
    std::array<char, N> buffer{};
    size_t pos = 0;

    constexpr constexpr_sstream &operator<<(char c) {
      if (pos < N - 1)
        buffer[pos++] = c; //NOLINT
      else
        throw "constexpr_sstream overflow";
      return *this;
    }

    constexpr constexpr_sstream &operator<<(const char *s) {
      while (*s) operator<<(*s++); // NOLIN
      // T
      return *this;
    }

    constexpr constexpr_sstream &operator<<(std::integral auto x) {
      if (x < 0) return (*this) << "-" << -x;
      int len = 0;
      char digits[10];                  // NOLINT
      do {                              // NOLINT
        digits[len++] = '0' + (x % 10); // NOLINT
        x /= 10;                        // NOLINT
      } while (x);
      for (int i = len - 1; i >= 0; --i) operator<<(digits[i]); // NOLINT
      return *this;
    }

    constexpr const char *c_str() const { return buffer.data(); }

    constexpr size_t size() const {
      size_t len = 0;
      while (len < N && buffer[len] != '\0') ++len;
      //while (buffer[len] != '\0') ++len;
      return len;
    }

    constexpr std::array<char, N> str() const {
      std::array<char, N> res{};                           // init is required in constexpr
      for (size_t i = 0; i < pos; ++i) res[i] = buffer[i]; // NOLINT
      // res[pos] = '\0'; // null-terminate is guaranteed by init
      return res;
    }
  };

  template <size_t N> class string_literal {
    char value[N]; // NOLINT

    public:
    constexpr string_literal(const char (&str)[N]) {    // NOLINT
      for (size_t i = 0; i < N; ++i) value[i] = str[i]; // NOLINT
    }

    constexpr string_literal(std::array<char, N> const &s) { // NOLINT
      for (size_t i = 0; i < N; ++i) value[i] = s[i];        // NOLINT
    }

    constexpr size_t size() const {
      size_t len = 0;
      while (value[len] != '\0') ++len;
      return len;
    }
    constexpr const char *c_str() const { return value; }
  };

  template <size_t N, size_t P> constexpr constexpr_sstream<N> &operator<<(constexpr_sstream<N> &ss, string_literal<P> const &s) {
    return ss << s.c_str(); // or s.data() if you prefer
  }

} // namespace c2py
