#include <c2py/c2py.hpp>

#ifndef C2PY_HXX_DECLARATION_namespace_GUARDS
#define C2PY_HXX_DECLARATION_namespace_GUARDS
template <> constexpr bool c2py::is_wrapped<A::C>                                = true;
template <> inline constexpr auto c2py::tp_name<A::C>                            = "namespace.C";
template <> constexpr bool c2py::is_wrapped<A::C::E1>                            = true;
template <> const std::map<A::C::E1, std::string> c2py::enum_to_string<A::C::E1> = {{A::C::E1::a, "a"}, {A::C::E1::b, "b"}, {A::C::E1::c, "c"}};
#endif