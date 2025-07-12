#include <c2py/c2py.hpp>

#ifndef C2PY_HXX_DECLARATION_cls_basic_GUARDS
#define C2PY_HXX_DECLARATION_cls_basic_GUARDS
template <> constexpr bool c2py::is_wrapped<A>           = true;
template <> constexpr bool c2py::is_wrapped<dummy_class> = true;
#endif