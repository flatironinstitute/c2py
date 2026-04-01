#include <c2py/c2py.hpp>

#ifndef C2PY_HXX_DECLARATION_cls_der_GUARDS
#define C2PY_HXX_DECLARATION_cls_der_GUARDS
template <> constexpr bool c2py::is_wrapped<B>     = true;
template <> inline constexpr auto c2py::tp_name<B> = "cls_der.B";
template <> constexpr bool c2py::is_wrapped<A>     = true;
template <> inline constexpr auto c2py::tp_name<A> = "cls_der.A";
template <> constexpr bool c2py::is_wrapped<D>     = true;
template <> inline constexpr auto c2py::tp_name<D> = "cls_der.D";
#endif