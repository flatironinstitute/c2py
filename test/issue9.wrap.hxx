#include <c2py/c2py.hpp>

#ifndef C2PY_HXX_DECLARATION_issue9_GUARDS
#define C2PY_HXX_DECLARATION_issue9_GUARDS
template <> constexpr bool c2py::is_wrapped<dummy_class>     = true;
template <> inline constexpr auto c2py::tp_name<dummy_class> = "issue9.DummyClass";
#endif