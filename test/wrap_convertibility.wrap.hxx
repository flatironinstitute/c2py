#include <c2py/c2py.hpp>

#ifndef C2PY_HXX_DECLARATION_wrap_convertibility_GUARDS
#define C2PY_HXX_DECLARATION_wrap_convertibility_GUARDS
template <> constexpr bool c2py::is_wrapped<A>     = true;
template <> inline constexpr auto c2py::tp_name<A> = "wrap_convertibility.A";
template <> constexpr bool c2py::is_wrapped<B>     = true;
template <> inline constexpr auto c2py::tp_name<B> = "wrap_convertibility.B";
#endif