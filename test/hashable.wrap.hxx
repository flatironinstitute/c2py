#include <c2py/c2py.hpp>

#ifndef C2PY_HXX_DECLARATION_hashable_GUARDS
#define C2PY_HXX_DECLARATION_hashable_GUARDS
template <> constexpr bool c2py::is_wrapped<N::cls_hashable>         = true;
template <> inline constexpr auto c2py::tp_name<N::cls_hashable>     = "hashable.ClsHashable";
template <> constexpr bool c2py::is_wrapped<N::cls_not_hashable>     = true;
template <> inline constexpr auto c2py::tp_name<N::cls_not_hashable> = "hashable.ClsNotHashable";
#endif