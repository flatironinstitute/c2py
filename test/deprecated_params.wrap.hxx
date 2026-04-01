#include <c2py/c2py.hpp>

#ifndef C2PY_HXX_DECLARATION_deprecated_params_GUARDS
#define C2PY_HXX_DECLARATION_deprecated_params_GUARDS
template <> constexpr bool c2py::is_wrapped<MyClass>     = true;
template <> inline constexpr auto c2py::tp_name<MyClass> = "deprecated_params.MyClass";
#endif