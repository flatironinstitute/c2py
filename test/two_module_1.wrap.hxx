#include <c2py/c2py.hpp>

#ifndef C2PY_HXX_DECLARATION_two_module_1_GUARDS
#define C2PY_HXX_DECLARATION_two_module_1_GUARDS
template <> constexpr bool c2py::is_wrapped<N::A>     = true;
template <> inline constexpr auto c2py::tp_name<N::A> = "two_module_1.A";
template <> constexpr bool c2py::is_wrapped<N::Color> = true;
template <>
const std::map<N::Color, str_t> c2py::enum_to_string<N::Color> = {{N::Color::Red, "Red"}, {N::Color::Green, "Green"}, {N::Color::Blue, "Blue"}};
template <> constexpr bool c2py::is_wrapped<N::Direction>      = true;
template <>
const std::map<N::Direction, str_t> c2py::enum_to_string<N::Direction> = {{N::Direction::North, "North"},
                                                                          {N::Direction::South, "South"},
                                                                          {N::Direction::East, "East"},
                                                                          {N::Direction::West, "West"}};
#endif