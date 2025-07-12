#include <c2py/c2py.hpp>

#ifndef C2PY_HXX_DECLARATION_comparison_GUARDS
#define C2PY_HXX_DECLARATION_comparison_GUARDS
template <> constexpr bool c2py::is_wrapped<N::cls_equal>  = true;
template <> constexpr bool c2py::is_wrapped<N::cls_equal2> = true;
template <> constexpr bool c2py::is_wrapped<N::cls_comp>   = true;
#endif