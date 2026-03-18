#include <c2py/c2py.hpp>

#ifndef C2PY_HXX_DECLARATION_properties_GUARDS
#define C2PY_HXX_DECLARATION_properties_GUARDS
template <> constexpr bool c2py::is_wrapped<A>     = true;
template <> inline constexpr auto c2py::tp_name<A> = "properties.A";
template <> constexpr bool c2py::is_wrapped<B>     = true;
template <> inline constexpr auto c2py::tp_name<B> = "properties.B";
template <> constexpr bool c2py::is_wrapped<C>     = true;
template <> inline constexpr auto c2py::tp_name<C> = "properties.C";
#endif