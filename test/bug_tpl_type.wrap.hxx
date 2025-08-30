#include <c2py/c2py.hpp>

#ifndef C2PY_HXX_DECLARATION_bug_tpl_type_GUARDS
#define C2PY_HXX_DECLARATION_bug_tpl_type_GUARDS
template <> constexpr bool c2py::is_wrapped<C>          = true;
template <> inline constexpr auto c2py::tp_name<C>      = "bug_tpl_type.C";
template <> constexpr bool c2py::is_wrapped<A<3>>       = true;
template <> inline constexpr auto c2py::tp_name<A<3>>   = "bug_tpl_type.A3";
template <> constexpr bool c2py::is_wrapped<B<int>>     = true;
template <> inline constexpr auto c2py::tp_name<B<int>> = "bug_tpl_type.Bi";
#endif