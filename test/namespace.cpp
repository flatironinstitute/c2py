#include <c2py/c2py.hpp>
#include <iostream>

namespace A {
  void funcA() { std::cout << "Function in namespace A" << std::endl; }

  namespace B {
    void funcB() { std::cout << "Function in namespace A::B" << std::endl; }
  } // namespace B

  namespace detail {
    void funcDetail() { std::cout << "Function in namespace A::detail" << std::endl; }
  } // namespace detail
} // namespace A

#include "namespace.wrap.cxx"
