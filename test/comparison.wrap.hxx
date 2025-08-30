#include <c2py/c2py.hpp>

#ifndef C2PY_HXX_DECLARATION_comparison_GUARDS
#define C2PY_HXX_DECLARATION_comparison_GUARDS
template <> constexpr bool c2py::is_wrapped<N::cls_equal>      = true;
template <> inline constexpr auto c2py::tp_name<N::cls_equal>  = "comparison.ClsEqual";
template <> constexpr bool c2py::is_wrapped<N::cls_equal2>     = true;
template <> inline constexpr auto c2py::tp_name<N::cls_equal2> = "comparison.ClsEqual2";
template <> constexpr bool c2py::is_wrapped<N::cls_comp>       = true;
template <> inline constexpr auto c2py::tp_name<N::cls_comp>   = "comparison.ClsComp";
#endif