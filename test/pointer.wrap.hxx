#include <c2py/c2py.hpp>

#ifndef C2PY_HXX_DECLARATION_pointer_GUARDS
#define C2PY_HXX_DECLARATION_pointer_GUARDS
template <> constexpr bool c2py::is_wrapped<a_struct> = true;
#endif