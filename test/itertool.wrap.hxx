#include <c2py/c2py.hpp>

#ifndef C2PY_HXX_DECLARATION_itertool_GUARDS
#define C2PY_HXX_DECLARATION_itertool_GUARDS
template <> constexpr bool c2py::is_wrapped<a_class>     = true;
template <> inline constexpr auto c2py::tp_name<a_class> = "itertool.AClass";
#endif