#include <c2py/c2py.hpp>

#ifndef C2PY_HXX_DECLARATION_ignore_GUARDS
#define C2PY_HXX_DECLARATION_ignore_GUARDS
template <> constexpr bool c2py::is_wrapped<a_struct>     = true;
template <> inline constexpr auto c2py::tp_name<a_struct> = "ignore.AStruct";
template <> constexpr bool c2py::is_wrapped<opaque>       = true;
template <> inline constexpr auto c2py::tp_name<opaque>   = "ignore.Opaque";
template <> constexpr bool c2py::is_wrapped<opaque2>      = true;
template <> inline constexpr auto c2py::tp_name<opaque2>  = "ignore.Opaque2";
#endif