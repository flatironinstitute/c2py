#include <c2py/c2py.hpp>

#ifndef C2PY_HXX_DECLARATION_ignore_GUARDS
#define C2PY_HXX_DECLARATION_ignore_GUARDS
template <> constexpr bool c2py::is_wrapped<a_struct> = true;
template <> constexpr bool c2py::is_wrapped<opaque>   = true;
template <> constexpr bool c2py::is_wrapped<opaque2>  = true;
#endif