#include <c2py/c2py.hpp>

#ifndef C2PY_HXX_DECLARATION_namespace_GUARDS
#define C2PY_HXX_DECLARATION_namespace_GUARDS
template <> constexpr bool c2py::is_wrapped<A::C>     = true;
template <> inline constexpr auto c2py::tp_name<A::C> = "namespace.C";
#endif