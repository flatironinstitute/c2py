#include <c2py/c2py.hpp>

#ifndef C2PY_HXX_DECLARATION_tpl_derived_GUARDS
#define C2PY_HXX_DECLARATION_tpl_derived_GUARDS
template <> constexpr bool c2py::is_wrapped<N::my_base>      = true;
template <> inline constexpr auto c2py::tp_name<N::my_base>  = "tpl_derived.MyBase";
template <> constexpr bool c2py::is_wrapped<N::my_class>     = true;
template <> inline constexpr auto c2py::tp_name<N::my_class> = "tpl_derived.MyClass";
#endif