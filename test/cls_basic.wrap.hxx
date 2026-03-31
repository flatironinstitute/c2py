#include <c2py/c2py.hpp>

#ifndef C2PY_HXX_DECLARATION_cls_basic_GUARDS
#define C2PY_HXX_DECLARATION_cls_basic_GUARDS
template <> constexpr bool c2py::is_wrapped<A>               = true;
template <> inline constexpr auto c2py::tp_name<A>           = "cls_basic.A";
template <> constexpr bool c2py::is_wrapped<dummy_class>     = true;
template <> inline constexpr auto c2py::tp_name<dummy_class> = "cls_basic.DummyClass";
template <> constexpr bool c2py::is_wrapped<some_class>      = true;
template <> inline constexpr auto c2py::tp_name<some_class>  = "cls_basic.renamed_class";
template <> constexpr bool c2py::is_wrapped<ns::B>           = true;
template <> inline constexpr auto c2py::tp_name<ns::B>       = "cls_basic.B";
#endif