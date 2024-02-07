#pragma once
#include <string>
#include "util/str.hpp"
#include "util/type_name.hpp"

namespace c2py {

  // ------------ cpp_name --------------
  // name of the c++ type for error messages and signatures

  // FIXME : constexpr when implemented in clang 2b
  template <typename T> static inline const std::string cpp_name = trim(replacenl(std::string{util::type_name<T>()})); // typeid(T).name();

  // FIXME : if the first option is not ok, we have to enumerate all basic types , etc...
  // And specialize for all converters ?
  //template <> inline const std::string cpp_name<int>                      = "int";
  //template <typename T> static inline const std::string cpp_name<T &>     = cpp_name<T> + '&';
  //template <typename T> static inline const std::string cpp_name<T const> = cpp_name<T> + " const ";

  // Another option is to use reflection in the cxx generation with
  // adding all cpp_name<> which the compiler has seen and wrapped ...

} // namespace c2py
