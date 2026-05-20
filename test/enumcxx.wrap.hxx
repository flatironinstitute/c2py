#include <c2py/c2py.hpp>

#ifndef C2PY_HXX_DECLARATION_enumcxx_GUARDS
#define C2PY_HXX_DECLARATION_enumcxx_GUARDS
template <> constexpr bool c2py::is_wrapped<D>                       = true;
template <> inline constexpr auto c2py::tp_name<D>                   = "enumcxx.D";
template <> constexpr bool c2py::is_wrapped<E1>                      = true;
template <> const std::map<E1, str_t> c2py::enum_to_string<E1>       = {{E1::a, "a"}, {E1::b, "b"}, {E1::c, "c"}};
template <> constexpr bool c2py::is_wrapped<E2>                      = true;
template <> const std::map<E2, str_t> c2py::enum_to_string<E2>       = {{E2::A, "A"}, {E2::B, "B"}, {E2::C, "C"}};
template <> constexpr bool c2py::is_wrapped<D::E3>                   = true;
template <> const std::map<D::E3, str_t> c2py::enum_to_string<D::E3> = {{D::E3::d, "d"}, {D::E3::e, "e"}, {D::E3::f, "f"}};
#endif