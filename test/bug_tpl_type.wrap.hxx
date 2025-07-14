#include <c2py/c2py.hpp>

#ifndef C2PY_HXX_DECLARATION_bug_tpl_type_GUARDS
#define C2PY_HXX_DECLARATION_bug_tpl_type_GUARDS
template <> constexpr bool c2py::is_wrapped<C>      = true;
template <> constexpr bool c2py::is_wrapped<A<3>>   = true;
template <> constexpr bool c2py::is_wrapped<B<int>> = true;
#endif